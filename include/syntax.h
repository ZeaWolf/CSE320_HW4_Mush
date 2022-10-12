/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

/*
 * The elements of this enumerated type are used in the "class" field
 * of the "STMT" structure to specify the particular kind of statement
 * that the structure represents.  The parenthesized names in the comments
 * indicate which element (if any) of the "members" union in the STMT
 * structure is used by each kind of statement.
 */
typedef enum {
    NO_STMT_CLASS,
    LIST_STMT_CLASS,            // "list" statement
    DELETE_STMT_CLASS,          // "delete" statement (delete_stmt)
    RUN_STMT_CLASS,             // "run" statement
    CONT_STMT_CLASS,            // "cont" statement
    STOP_STMT_CLASS,            // "stop" statement
    WAIT_STMT_CLASS,            // "wait" statement (jobctl_stmt)
    POLL_STMT_CLASS,            // "poll" statement (jobctl_stmt)
    CANCEL_STMT_CLASS,          // "cancel" statement (jobctl_stmt)
    PAUSE_STMT_CLASS,           // "pause" statement
    SET_STMT_CLASS,             // "set" statement (set_stmt)
    UNSET_STMT_CLASS,           // "unset" statement (unset_stmt)
    IF_STMT_CLASS,              // "if" statement (if_stmt)
    GOTO_STMT_CLASS,            // "goto" statement (goto_stmt)
    SOURCE_STMT_CLASS,          // "source" statement (source_stmt)
    FG_STMT_CLASS,              // pipeline run in foreground (sys_stmt)
    BG_STMT_CLASS               // pipeline run in background (sys_stmt)
} STMT_CLASS;

/*
 * This structure is used to represent a statement.
 * The value in the "class" field tells what kind of statement it is.
 * Depending on this value, one of the fields of the "members" union
 * may be valid.
 */
typedef struct stmt {
    STMT_CLASS class;
    int lineno;
    union {
	struct {
	    int from;
	    int to;
	} delete_stmt;
	struct {
	    struct pipeline *pipeline;
	} sys_stmt;
	struct {
	    struct expr *expr;
	} jobctl_stmt;
	struct {
	    char *name;
	    struct expr *expr;
	} set_stmt;
	struct {
	    char *name;
	} unset_stmt;
	struct {
	    struct expr *expr;
	    int lineno;
	} if_stmt;
	struct {
	    int lineno;
	} goto_stmt;
	struct {
	    char *file;
	} source_stmt;
    } members;
} STMT;

/*
 * This structure is used to represent a command.  The "args" field points
 * to the head of as a nonempty linked list of "args" that make up the command.
 * The first "arg" is interpreted as the name of the command; the remainder
 * are arguments to it.  The "next" field is used to link commands into a
 * pipeline.
 */
typedef struct command {
    struct arg *args;
    struct command *next;
} COMMAND;

/*
 * This structure is used to represent a "pipeline".  The "commands" field
 * points to the head of a nonempty list of commands.  The "input_file" field,
 * if non-NULL, is the name of a file from which input to the first command
 * in the pipeline is to be redirected.  Similarly, the "output_file" field,
 * if non-NULL, is the name of a file to which output from the last command
 * in the pipeline is to be redirected.  If the "capture_output" field is
 * nonzero, then instead of being redirected to a file, the output from the
 * last command in the pipeline is to be redirected to a pipe.  This pipe is
 * to be read by the main process, which will "captures" the output and make
 * it available as the value of a variable in the data store.
 */
typedef struct pipeline {
    COMMAND *commands;
    char *input_file;
    char *output_file;
    int capture_output;
} PIPELINE;

/*
 * Values of this enumerated type are used to identify the various kinds
 * of expressions.
 */
typedef enum {
    NO_EXPR_CLASS,
    LIT_EXPR_CLASS,             // literal string (value)
    NUM_EXPR_CLASS,             // numeric variable (variable)
    STRING_EXPR_CLASS,          // string variable (variable)
    UNARY_EXPR_CLASS,           // unary expression (unary_expr)
    BINARY_EXPR_CLASS           // binary expression (binary_expr)
} EXPR_CLASS;

/*
 * Values of this enumerated type are used to identify the various kinds
 * of operators in expressions.
 */
typedef enum {
    NO_OPRTR,
    NOT_OPRTR,                  // "not" operator (unary_expr)
    AND_OPRTR,                  // "and" operator (binary_expr)
    OR_OPRTR,                   // "or" operator (binary_expr)
    EQUAL_OPRTR,                // "equal to" operator (binary_expr)
    LESS_OPRTR,                 // "less than" operator (binary_expr)
    GREATER_OPRTR,              // "greater than" operator (binary_expr)
    LESSEQ_OPRTR,               // "less than or equal" operator (binary_expr)
    GREATEQ_OPRTR,              // "greater than or equal" operator (binary_expr)
    PLUS_OPRTR,                 // "plus" (binary_expr)
    MINUS_OPRTR,                // "minus" (binary_expr)
    TIMES_OPRTR,                // "times" (binary_expr)
    DIVIDE_OPRTR,               // "divide" (binary_expr)
    MOD_OPRTR                   // "mod" (binary_expr)
} OPRTR;

/*
 * Values of this enumerated type are used to identify the various kinds
 * values that an expression can have.
 */
typedef enum {
    NO_VALUE_TYPE,
    NUM_VALUE_TYPE,              // numeric value
    STRING_VALUE_TYPE            // string value
} VALUE_TYPE;

/*
 * This structure is used to represent an "expression".
 */
typedef struct expr {
    EXPR_CLASS class;
    VALUE_TYPE type;
    union {
	char *variable;
	char *value;
	struct {
	    OPRTR oprtr;
	    struct expr *arg;
	} unary_expr;
	struct {
	    OPRTR oprtr;
	    struct expr *arg1;
	    struct expr *arg2;
	} binary_expr;
    } members;
} EXPR;

/*
 * This structure is used to represent an "argument", which is
 * a single element of a command.  Arguments contain arbitrary expressions,
 * which allows commands to be constructed that depend on the values
 * of variables.
 */
typedef struct arg {
    EXPR *expr;
    struct arg *next;
} ARG;

/*
 * The following functions are used to print representations
 * of the various syntactic objects to a specified output stream.
 * A nonzero value for the "parens" argument of show_expr() causes
 * a compound expression to be printed within enclosing parentheses.
 */
void show_stmt(FILE *file, STMT *stmt);
void show_pipeline(FILE *file, PIPELINE *pline);
void show_command(FILE *file, COMMAND *cmd);
void show_expr(FILE *file, EXPR *expr, int parens);
void show_oprtr(FILE *file, OPRTR oprtr);
void show_lineno(FILE *file, int lineno);

/*
 * The following functions are use to free the various syntactic
 * objects.  Freeing an object with one of these functions implies
 * freeing all the objects that it references.
 */
void free_stmt(STMT *stmt);
void free_pipeline(PIPELINE *pline);
void free_commands(COMMAND *cmd);
void free_args(ARG *args);
void free_expr(EXPR *expr);
void free_oprtr(OPRTR oprtr);

/*
 * The following functions are use to make deep copies of the
 * various syntactic objects.
 */
PIPELINE *copy_pipeline(PIPELINE *pline);
COMMAND *copy_commands(COMMAND *cmd);
ARG *copy_args(ARG *args);
EXPR *copy_expr(EXPR *expr);
