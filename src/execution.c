/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "mush.h"
#include "mush.tab.h"
#include "debug.h"

/*
 * Mush: Execution engine.
 */

extern int yylex_destroy();
extern void push_input(FILE *in);
extern int pop_input(void);
extern int input_depth(void);
extern STMT *mush_parsed_stmt;

static int exec_run();
static int exec_cont();

#define PROMPT "mush: "

/* Uncomment this to enable tracing of the parser. */
//int yydebug = 1;

/*
 * A quit handler is installed to allow user-initiated escape
 * from constructs that wait for signals.
 */
static volatile sig_atomic_t got_quit = 0;

static void handler(int sig) {
    got_quit = 1;
}

/*
 * Target for longjmp() to jump to after a low-level error has
 * occurred, e.g. in expression evaluation.
 */
static jmp_buf onerror;

/*
 * Top-level interpreter loop.
 * Reads single statements from stdin and either inserts them into the program,
 * if they have a line number, otherwise executes them immediately.
 */
int exec_interactive() {
    signal(SIGQUIT, SIG_IGN);
    while(1) {
	if(!input_depth() && isatty(fileno(stdin)))
	    fprintf(stdout, "%s", PROMPT);
	fflush(stdout);
	if(!yyparse()) {
	    STMT *stmt = mush_parsed_stmt;
	    if(stmt != NULL) {
		if(stmt->lineno) {
		    prog_insert(stmt);
		} else {
		    if(stmt->class == RUN_STMT_CLASS) {
			free_stmt(stmt);
			stmt = NULL;
			exec_run();
		    } else if(stmt->class == CONT_STMT_CLASS) {
			free_stmt(stmt);
			stmt = NULL;
			exec_cont();
		    } else {
			exec_stmt(stmt);
			free_stmt(stmt);
			stmt = NULL;
		    }
		}
	    }
	} else {
	    if(pop_input())
		break;
	}
	if(!input_depth() && isatty(fileno(stdin))) {
	    store_show(stderr);
	    fprintf(stderr, "\n");
	    jobs_show(stderr);
	}
    }
    yylex_destroy();
    return 0;
}

/*
 * Enter an execution loop starting at the beginning of the program.
 */
static int exec_run() {
    prog_reset();
    return exec_cont();
}

/*
 * Enter an execution loop starting at the current line number.
 */
static int exec_cont() {
    int err = 0;
    STMT *stmt;
    stmt = prog_fetch();
    if(stmt == NULL) {
	fprintf(stderr, "No statement to execute\n");
	return -1;
    }
    if(setjmp(onerror))
	return -1;
    signal(SIGQUIT, handler);
    while(!got_quit) {
	stmt = prog_fetch();
	if(!stmt) {
	    fprintf(stderr, "STOP (end of program)\n");
	    break;
	}
	prog_next();
	err = exec_stmt(stmt);
	if(err)
	    break;
    }
    signal(SIGQUIT, SIG_IGN);
    if(got_quit)
	fprintf(stderr, "Quit!\n");
    got_quit = 0;
    return err;
}

/*
 * Execute a statement.
 * This function is called from exec_run().
 * It can also be called separately to execute an individual statement
 * read interactively.
 *
 * Successful execution (except for STOP) returns 0.
 * Successful execution of STOP returns 1.
 * Unsuccessful execution returns -1.
 */
int exec_stmt(STMT *stmt) {
    int val; char *str;
    FILE *in;
    if(setjmp(onerror))
	return -1;
    if(stmt->lineno)
	debug("execute statement %d", stmt->lineno);
    switch(stmt->class) {
    case LIST_STMT_CLASS:
	prog_list(stdout);
	break;
    case DELETE_STMT_CLASS:
	prog_delete(stmt->members.delete_stmt.from, stmt->members.delete_stmt.to);
	break;
    case STOP_STMT_CLASS:
	if(stmt->lineno)
	    fprintf(stderr, "STOP at line %d\n", stmt->lineno);
	return 1;
    case GOTO_STMT_CLASS:
	if(!prog_goto(stmt->members.goto_stmt.lineno))
	    return -1;
	break;
    case SET_STMT_CLASS:
	switch(stmt->members.set_stmt.expr->type) {
	case NUM_VALUE_TYPE:
	    val = eval_to_numeric(stmt->members.set_stmt.expr);
	    store_set_int(stmt->members.set_stmt.name, val);
	    break;
	case STRING_VALUE_TYPE:
	    str = eval_to_string(stmt->members.set_stmt.expr);
	    store_set_string(stmt->members.set_stmt.name, str);
	    break;
	default:
	    break;
	}
	break;
    case UNSET_STMT_CLASS:
	store_set_string(stmt->members.unset_stmt.name, NULL);
	break;
    case IF_STMT_CLASS:
	val = eval_to_numeric(stmt->members.if_stmt.expr);
	if(val) {
	    if(!prog_goto(stmt->members.if_stmt.lineno))
		return -1;
	    else
		return 0;
	}
	break;
    case SOURCE_STMT_CLASS:
	in = fopen(stmt->members.source_stmt.file, "r");
	if(!in) {
	    fprintf(stderr, "Couldn't open source file: '%s'\n",
		    stmt->members.source_stmt.file);
	    return -1;
	}
	push_input(in);
	break;
    case FG_STMT_CLASS:
	{
	    PIPELINE *pp = stmt->members.sys_stmt.pipeline;
	    int job = jobs_run(pp);
	    store_set_int(JOB_VAR, job);
	    int status = jobs_wait(job);
	    store_set_int(STATUS_VAR, status);
	    if(pp->capture_output) {
		char *output = jobs_get_output(job);
		debug("Captured output: '%s'", output);
		store_set_string(OUTPUT_VAR, output);
	    }
	    jobs_expunge(job);
	}
	break;
    case BG_STMT_CLASS:
	{
	    int job = jobs_run(stmt->members.sys_stmt.pipeline);
	    store_set_int(JOB_VAR, job);
	}
	break;
    case WAIT_STMT_CLASS:
	{
	    int job = eval_to_numeric(stmt->members.jobctl_stmt.expr);
	    int status = jobs_wait(job);
	    store_set_int(STATUS_VAR, status);
	    char *output = jobs_get_output(job);
	    if(output)
		store_set_string(OUTPUT_VAR, output);
	    jobs_expunge(job);
	}
	break;
    case POLL_STMT_CLASS:
	{
	    int job = eval_to_numeric(stmt->members.jobctl_stmt.expr);
	    int status = jobs_poll(job);
	    store_set_int(STATUS_VAR, status);
	    if(status >= 0) {
		char *output = jobs_get_output(job);
		if(output)
		    store_set_string(OUTPUT_VAR, output);
		jobs_expunge(job);
	    }
	}
	break;
    case CANCEL_STMT_CLASS:
	{
	    int job = eval_to_numeric(stmt->members.jobctl_stmt.expr);
	    jobs_cancel(job);
	}
	break;
    case PAUSE_STMT_CLASS:
	{
	    jobs_pause();
	}
	break;
    default:
	fprintf(stderr, "Unknown statement class: %d\n", stmt->class);
	abort();
    }
    return 0;
}

/*
 * Evaluate an expression, returning an integer result.
 * It is assumed that the jmp_buf onerror has been initialized by the caller
 * with a control point to escape to in case there is an error during evaluation.
 */
long eval_to_numeric(EXPR *expr) {
    char *endp, *str1, *str2;
    long opr1, opr2;
    int err;
    switch(expr->class) {
    case LIT_EXPR_CLASS:
	opr1 = strtol(expr->members.value, &endp, 0);
	if(*endp == '\0') {
	    return opr1;
	} else {
	    fprintf(stderr, "Literal '%s' is not an integer\n", expr->members.value);
	    longjmp(onerror, 0);
	}
    case STRING_EXPR_CLASS:
    case NUM_EXPR_CLASS:
	err = store_get_int(expr->members.variable, &opr1);
	if(err) {
	    fprintf(stderr, "Variable %s does not have an integer value\n",
		    expr->members.variable);
	    longjmp(onerror, 0);
	}
	return opr1;
	fprintf(stderr, "String variable %s in expression not implemented\n",
		expr->members.variable);
	abort();
    case UNARY_EXPR_CLASS:
	opr1 = eval_to_numeric(expr->members.unary_expr.arg);
	switch(expr->members.unary_expr.oprtr) {
	case NOT_OPRTR:
	    return opr1 ? 0 : 1;
	default:
	    fprintf(stderr, "Unknown unary numeric operator: %d\n",
		    expr->members.unary_expr.oprtr);
	    abort();
	}
    case BINARY_EXPR_CLASS:
	if(expr->members.binary_expr.oprtr == EQUAL_OPRTR) {
	    if(expr->members.binary_expr.arg1->type == NUM_VALUE_TYPE &&
	       expr->members.binary_expr.arg2->type == NUM_VALUE_TYPE) {
		opr1 = eval_to_numeric(expr->members.binary_expr.arg1);
		opr2 = eval_to_numeric(expr->members.binary_expr.arg2);
		return opr1 == opr2;
	    } else {
		str1 = eval_to_string(expr->members.binary_expr.arg1);
		str2 = eval_to_string(expr->members.binary_expr.arg2);
		return !strcmp(str1, str2);
	    }
	}
	opr1 = eval_to_numeric(expr->members.binary_expr.arg1);
	opr2 = eval_to_numeric(expr->members.binary_expr.arg2);
	switch(expr->members.binary_expr.oprtr) {
	case AND_OPRTR:
	    return opr1 && opr2;
	case OR_OPRTR:
	    return opr1 || opr2;
	case PLUS_OPRTR:
	    return opr1 + opr2;
	case MINUS_OPRTR:
	    return opr1 - opr2;
	case TIMES_OPRTR:
	    return opr1 * opr2;
	case DIVIDE_OPRTR:
	    return opr1 / opr2;
	case MOD_OPRTR:
	    return opr1 % opr2;
	case LESS_OPRTR:
	    return opr1 < opr2;
	case GREATER_OPRTR:
	    return opr1 > opr2;
	case LESSEQ_OPRTR:
	    return opr1 <= opr2;
	case GREATEQ_OPRTR:
	    return opr1 >= opr2;
	default:
	    fprintf(stderr, "Unknown binary numeric operator: %d\n",
		    expr->members.binary_expr.oprtr);
	    abort();
	}
    default:
	fprintf(stderr, "Unknown expression class: %d\n", expr->class);
	abort();
    }
    return 0;
}

/*
 * Evaluate an expression, returning a string result.
 * It is assumed that the jmp_buf onerror has been initialized by the caller
 * with a control point to escape to in case there is an error during evaluation.
 */
char *eval_to_string(EXPR *expr) {
    char *str1, *str2;
    switch(expr->class) {
    case LIT_EXPR_CLASS:
	return expr->members.value;
    case NUM_EXPR_CLASS:
    case STRING_EXPR_CLASS:
	str1 = store_get_string(expr->members.variable);
	if(!str1) {
	    fprintf(stderr, "Variable %s does not have a value\n",
		    expr->members.variable);
	    longjmp(onerror, 0);
	}
	return str1;
    case UNARY_EXPR_CLASS:
	str1 = eval_to_string(expr->members.unary_expr.arg);
	switch(expr->members.unary_expr.oprtr) {
	default:
	    (void)str1;
	    fprintf(stderr, "Unknown unary string operator: %d\n",
		    expr->members.unary_expr.oprtr);
	    abort();
	}
    case BINARY_EXPR_CLASS:
	str1 = eval_to_string(expr->members.binary_expr.arg1);
	str2 = eval_to_string(expr->members.binary_expr.arg2);
	switch(expr->members.binary_expr.oprtr) {
	default:
	    (void)str1;  (void)str2;
	    fprintf(stderr, "Unknown binary string operator: %d\n",
		    expr->members.binary_expr.oprtr);
	    abort();
	}
    default:
	fprintf(stderr, "Unknown expression class: %d\n", expr->class);
	abort();
    }
    return 0;
}
