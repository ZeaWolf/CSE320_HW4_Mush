/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "syntax.h"

/*
 * Mush: Functions for manipulating syntax trees.
 */

void show_stmt(FILE *file, STMT *stmt) {
    show_lineno(file, stmt->lineno);
    switch(stmt->class) {
    case LIST_STMT_CLASS:
	fprintf(file, "list");
	break;
    case DELETE_STMT_CLASS:
	fprintf(file, "delete %d, %d",
		stmt->members.delete_stmt.from,
		stmt->members.delete_stmt.to);
	break;
    case RUN_STMT_CLASS:
	fprintf(file, "run");
	break;
    case CONT_STMT_CLASS:
	fprintf(file, "cont");
	break;
    case STOP_STMT_CLASS:
	fprintf(file, "stop");
	break;
    case FG_STMT_CLASS:
	show_pipeline(file, stmt->members.sys_stmt.pipeline);
	break;
    case BG_STMT_CLASS:
	show_pipeline(file, stmt->members.sys_stmt.pipeline);
	fprintf(file, "& ");
	break;
    case WAIT_STMT_CLASS:
	fprintf(file, "wait ");
	show_expr(file, stmt->members.jobctl_stmt.expr, 0);
	break;
    case POLL_STMT_CLASS:
	fprintf(file, "poll ");
	show_expr(file, stmt->members.jobctl_stmt.expr, 0);
	break;
    case CANCEL_STMT_CLASS:
	fprintf(file, "cancel ");
	show_expr(file, stmt->members.jobctl_stmt.expr, 0);
	break;
    case PAUSE_STMT_CLASS:
	fprintf(file, "pause");
	break;
    case SET_STMT_CLASS:
	fprintf(file, "set ");
	fprintf(file, "%s = ", stmt->members.set_stmt.name);
	show_expr(file, stmt->members.set_stmt.expr, 0);
	break;
    case UNSET_STMT_CLASS:
	fprintf(file, "unset ");
	fprintf(file, "%s", stmt->members.unset_stmt.name);
	break;
    case IF_STMT_CLASS:
	fprintf(file, "if ");
	show_expr(file, stmt->members.if_stmt.expr, 0);
	fprintf(file, " goto %d", stmt->members.if_stmt.lineno);
	break;
    case GOTO_STMT_CLASS:
	fprintf(file, "goto %d", stmt->members.goto_stmt.lineno);
	break;
    case SOURCE_STMT_CLASS:
	fprintf(file, "source %s", stmt->members.source_stmt.file);
	break;
    default:
	fprintf(stderr, "Unknown statement class: %d\n", stmt->class);
	abort();
    }
    fprintf(file, "\n");
}

void show_pipeline(FILE *file, PIPELINE *pline) {
    COMMAND *cmds = pline->commands;
    while(cmds) {
	show_command(file, cmds);
	if(cmds->next)
	    fprintf(file, " | ");
	cmds = cmds->next;
    }
    if(pline->input_file)
	fprintf(file, " < %s", pline->input_file);
    if(pline->capture_output)
	fprintf(file, " >@");
    if(pline->output_file)
	fprintf(file, " > %s", pline->output_file);
}

void show_command(FILE *file, COMMAND *cmd) {
    ARG *arg = cmd->args;
    while(arg) {
	show_expr(file, arg->expr, 0);
	if(arg->next)
	    fprintf(file, " ");
	arg = arg->next;
    }
}

void show_expr(FILE *file, EXPR *expr, int parens) {
    switch(expr->class) {
    case LIT_EXPR_CLASS:
	fprintf(file, "%s", expr->members.value);
	break;
    case NUM_EXPR_CLASS:
	fprintf(file, "#%s", expr->members.variable);
	break;
    case STRING_EXPR_CLASS:
	fprintf(file, "$%s", expr->members.variable);
	break;
    case UNARY_EXPR_CLASS:
	if(parens)
	    fprintf(file, "(");
	show_oprtr(file, expr->members.unary_expr.oprtr);
	fprintf(file, " ");
	show_expr(file, expr->members.unary_expr.arg, 1);
	if(parens)
	    fprintf(file, ")");
	break;
    case BINARY_EXPR_CLASS:
	if(parens)
	    fprintf(file, "(");
	show_expr(file, expr->members.binary_expr.arg1, 1);
	fprintf(file, " ");
	show_oprtr(file, expr->members.binary_expr.oprtr);
	fprintf(file, " ");
	show_expr(file, expr->members.binary_expr.arg2, 1);
	if(parens)
	    fprintf(file, ")");
	break;
    default:
	fprintf(stderr, "Unknown expression class: %d\n", expr->class);
	abort();
    }
}

void show_oprtr(FILE *file, OPRTR oprtr) {
    switch(oprtr) {
    case PLUS_OPRTR:
	fprintf(file, "+");
	break;
    case MINUS_OPRTR:
	fprintf(file, "-");
	break;
    case TIMES_OPRTR:
	fprintf(file, "*");
	break;
    case DIVIDE_OPRTR:
	fprintf(file, "/");
	break;
    case MOD_OPRTR:
	fprintf(file, "%s", "%");
	break;
    case AND_OPRTR:
	fprintf(file, "&&");
	break;
    case OR_OPRTR:
	fprintf(file, "||");
	break;
    case NOT_OPRTR:
	fprintf(file, "!");
	break;
    case EQUAL_OPRTR:
	fprintf(file, "==");
	break;
    case LESS_OPRTR:
	fprintf(file, "<");
	break;
    case GREATER_OPRTR:
	fprintf(file, ">");
	break;
    case LESSEQ_OPRTR:
	fprintf(file, "<=");
	break;
    case GREATEQ_OPRTR:
	fprintf(file, ">=");
	break;
    default:
	fprintf(stderr, "Unknown operator: %d\n", oprtr);
	abort();
    }
}

void show_lineno(FILE *file, int lineno) {
    if(lineno)
	fprintf(file, "%7d\t", lineno);
    else
	fprintf(file, "\t");
}

void free_stmt(STMT *stmt) {
    if(stmt == NULL)  // Produced by error recovery production
	return;
    switch(stmt->class) {
    case LIST_STMT_CLASS:
    case DELETE_STMT_CLASS:
    case RUN_STMT_CLASS:
    case CONT_STMT_CLASS:
    case STOP_STMT_CLASS:
	break;
    case FG_STMT_CLASS:
	free_pipeline(stmt->members.sys_stmt.pipeline);
	break;
    case BG_STMT_CLASS:
	free_pipeline(stmt->members.sys_stmt.pipeline);
	break;
    case GOTO_STMT_CLASS:
	break;
    case WAIT_STMT_CLASS:
    case POLL_STMT_CLASS:
    case CANCEL_STMT_CLASS:
	free_expr(stmt->members.jobctl_stmt.expr);
	break;
    case SET_STMT_CLASS:
	free(stmt->members.set_stmt.name);
	free_expr(stmt->members.set_stmt.expr);
	break;
    case UNSET_STMT_CLASS:
	free(stmt->members.unset_stmt.name);
	break;
    case IF_STMT_CLASS:
	free_expr(stmt->members.if_stmt.expr);
	break;
    case SOURCE_STMT_CLASS:
	free(stmt->members.source_stmt.file);
	break;
    case PAUSE_STMT_CLASS:
	break;
    default:
	fprintf(stderr, "Unknown statement class: %d\n", stmt->class);
	abort();
    }
    free(stmt);
}

void free_pipeline(PIPELINE *pline) {
    free_commands(pline->commands);
    if(pline->input_file)
	free(pline->input_file);
    if(pline->output_file)
	free(pline->output_file);
    free(pline);
}

void free_commands(COMMAND *cmd) {
    if(cmd->next)
	free_commands(cmd->next);
    if(cmd->args)
	free_args(cmd->args);
    free(cmd);
}

void free_args(ARG *args) {
    if(args->next)
	free_args(args->next);
    free_expr(args->expr);
    free(args);
}

void free_expr(EXPR *expr) {
    switch(expr->class) {
    case LIT_EXPR_CLASS:
	free(expr->members.value);
	break;
    case NUM_EXPR_CLASS:
	free(expr->members.variable);
	break;
    case STRING_EXPR_CLASS:
	free(expr->members.variable);
	break;
    case UNARY_EXPR_CLASS:
	free_expr(expr->members.unary_expr.arg);
	break;
    case BINARY_EXPR_CLASS:
	free_expr(expr->members.binary_expr.arg1);
	free_expr(expr->members.binary_expr.arg2);
	break;
    default:
	fprintf(stderr, "Unknown expression class: %d\n", expr->class);
	abort();
    }
    free(expr);
}

PIPELINE *copy_pipeline(PIPELINE *pline) {
    if(!pline)
	return NULL;
    PIPELINE *copy = calloc(sizeof(PIPELINE), 1);
    copy->commands = copy_commands(pline->commands);
    copy->capture_output = pline->capture_output;
    if(pline->input_file)
	copy->input_file = strdup(pline->input_file);
    if(pline->output_file)
	copy->output_file = strdup(pline->output_file);
    return(copy);
}

COMMAND *copy_commands(COMMAND *cmd) {
    if(!cmd)
	return NULL;
    COMMAND *copy = calloc(sizeof(COMMAND), 1);
    copy->next = copy_commands(cmd->next);
    copy->args = copy_args(cmd->args);
    return copy;
}

ARG *copy_args(ARG *args) {
    if(!args)
	return NULL;
    ARG *copy = calloc(sizeof(ARG), 1);
    copy->next = copy_args(args->next);
    copy->expr = copy_expr(args->expr);
    return copy;
}

EXPR *copy_expr(EXPR *expr) {
    if(!expr)
	return NULL;
    EXPR *copy = calloc(sizeof(EXPR), 1);
    copy->class = expr->class;
    copy->type = expr->type;
    switch(expr->class) {
    case LIT_EXPR_CLASS:
	copy->members.value = strdup(expr->members.value);
	break;
    case NUM_EXPR_CLASS:
	copy->members.variable = strdup(expr->members.variable);
	break;
    case STRING_EXPR_CLASS:
	copy->members.variable = strdup(expr->members.variable);
	break;
    case UNARY_EXPR_CLASS:
	copy->members.unary_expr.oprtr = expr->members.unary_expr.oprtr;
	copy->members.unary_expr.arg = copy_expr(expr->members.unary_expr.arg);
	break;
    case BINARY_EXPR_CLASS:
	copy->members.binary_expr.oprtr = expr->members.binary_expr.oprtr;
	copy->members.binary_expr.arg1 = copy_expr(expr->members.binary_expr.arg1);
	copy->members.binary_expr.arg2 = copy_expr(expr->members.binary_expr.arg2);
	break;
    default:
	fprintf(stderr, "Unknown expression class: %d\n", expr->class);
	abort();
    }
    return copy;
}
