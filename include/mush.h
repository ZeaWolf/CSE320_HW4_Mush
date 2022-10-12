/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

#include "syntax.h"

/* Names of special store variables to hold results from job execution. */
#define JOB_VAR "JOB"
#define STATUS_VAR "STATUS"
#define OUTPUT_VAR "OUTPUT"

/*
 * If you find it convenient, you may assume that the maximum number of jobs
 * that can exist at one time is given by the following preprocessor symbol.
 * Your code should continue to work even if the particular value of this
 * symbol is changed before compilation.
 */
#define MAX_JOBS 10

/* Functions in program store module. */
int prog_list(FILE *out);
int prog_insert(STMT *stmt);
int prog_delete(int min, int max);
void prog_reset();
STMT *prog_fetch();
STMT *prog_next();
STMT *prog_goto(int lineno);

/* Functions in data store module. */
char *store_get_string(char *var);
int store_get_int(char *var, long *valp);
int store_set_string(char *var, char *val);
int store_set_int(char *var, long val);
void store_show(FILE *f);

/* Functions in execution module. */
int exec_interactive();
int exec_stmt(STMT *stmt);
char *eval_to_string(EXPR *expr);
long eval_to_numeric(EXPR *expr);

/* Functions in jobs module. */
int jobs_init(void);
int jobs_fini(void);
int jobs_run(PIPELINE *pp);
int jobs_expunge(int jobid);
int jobs_wait(int jobid);
int jobs_poll(int jobid);
int jobs_cancel(int jobid);
int jobs_pause(void);
char *jobs_get_output(int jobid);
int jobs_show(FILE *file);
