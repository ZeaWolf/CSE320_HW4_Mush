#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#include "mush.h"
#include "debug.h"

/*
 * This is the "jobs" module for Mush.
 * It maintains a table of jobs in various stages of execution, and it
 * provides functions for manipulating jobs.
 * Each job contains a pipeline, which is used to initialize the processes,
 * pipelines, and redirections that make up the job.
 * Each job has a job ID, which is an integer value that is used to identify
 * that job when calling the various job manipulation functions.
 *
 * At any given time, a job will have one of the following status values:
 * "new", "running", "completed", "aborted", "canceled".
 * A newly created job starts out in with status "new".
 * It changes to status "running" when the processes that make up the pipeline
 * for that job have been created.
 * A running job becomes "completed" at such time as all the processes in its
 * pipeline have terminated successfully.
 * A running job becomes "aborted" if the last process in its pipeline terminates
 * with a signal that is not the result of the pipeline having been canceled.
 * A running job becomes "canceled" if the jobs_cancel() function was called
 * to cancel it and in addition the last process in the pipeline subsequently
 * terminated with signal SIGKILL.
 *
 * In general, there will be other state information stored for each job,
 * as required by the implementation of the various functions in this module.
 */
typedef struct job_node{
    struct job_node *prev;
    struct job_node *next;
    int job_id;
    pid_t pgid;
    char *status;
    int exit_status;
    int readfd;
    PIPELINE *pipeline;
    char *job_output;
}JOB_NODE;

typedef struct job_table{
    JOB_NODE *head;
}JOB_TABLE;

JOB_TABLE *jtable = NULL;

int jid = 0;

//static volatile sig_atomic_t got_child_status = 0;
int change_job_status(pid_t pid, char * status, int exit_status);
int read_output_capture(JOB_NODE *job);

static void child_handler(int sig) {
    sigset_t mask_all, prev_all;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    int olderrno = errno;
    int chstatus;
    pid_t pid;
    while((pid = waitpid(-1, &chstatus, 0))<=0)
        ;
    if(pid>0)
    {
        if(WIFSTOPPED(chstatus)|WIFSIGNALED(chstatus)|WIFEXITED(chstatus)){

            switch(WEXITSTATUS(chstatus))
            {
                case EXIT_SUCCESS:
                    change_job_status((pid_t)pid, "completed", chstatus);
                    break;
                case SIGKILL:
                    change_job_status((pid_t)pid, "canceled", chstatus);
                    break;
                default:
                    change_job_status((pid_t)pid, "aborted", chstatus);
            }
        }
    }
    errno = olderrno;
    sigprocmask(SIG_SETMASK, &prev_all, NULL);
    return;
}

static void io_handler(int sig){
    sigset_t mask_all, prev_all;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
    int olderrno = errno;

    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        read_output_capture(target);
        target=target->next;
    }

    errno = olderrno;
    sigprocmask(SIG_SETMASK, &prev_all, NULL);
    return;
}

int read_output_capture(JOB_NODE *job){
    if(job->readfd == -1)
        return -1;

    FILE *stream;
    char *buf, c;
    size_t len;

    stream = open_memstream(&buf, &len);
    while(read(job->readfd, &c, 1 ) > 0)
    {
        fprintf(stream, "%c", c);
    }
    fflush(stream);
    char *result = (char *)malloc(len);
    strncpy(result, buf, len);

    fclose(stream);
    if(len > 0)
    {
        if(job->job_output){
            job->job_output = (char *) realloc(job->job_output, (1+len+strlen(job->job_output)));
            job->job_output = strcat(job->job_output, result);
            free(result);
        }
        else{
            job->job_output = result;
        }
    }
    return 0;
}


/**
 * @brief  Initialize the jobs module.
 * @details  This function is used to initialize the jobs module.
 * It must be called exactly once, before any other functions of this
 * module are called.
 *
 * @return 0 if initialization is successful, otherwise -1.
 */
int jobs_init(void) {
    signal(SIGCHLD, child_handler);
    signal(SIGIO, io_handler);
    jtable = (JOB_TABLE *) malloc(sizeof(JOB_TABLE));
    if(jtable == NULL) return -1;
    JOB_NODE *dummy_head = (JOB_NODE *) malloc(sizeof(JOB_NODE));
    if(dummy_head == NULL) return -1;
    jtable->head = dummy_head;
    jtable->head->prev = dummy_head;
    jtable->head->next = dummy_head;
    jtable->head->job_id = -1;
    jtable->head->pgid = -1;
    jtable->head->status = "new";
    jtable->head->exit_status = -1;
    jtable->head->readfd = -1;
    jtable->head->pipeline = NULL;
    jtable->head->job_output = NULL;
    return 0;
}

/**
 * @brief  Finalize the jobs module.
 * @details  This function is used to finalize the jobs module.
 * It must be called exactly once when job processing is to be terminated,
 * before the program exits.  It should cancel all jobs that have not
 * yet terminated, wait for jobs that have been cancelled to terminate,
 * and then expunge all jobs before returning.
 *
 * @return 0 if finalization is completely successful, otherwise -1.
 */
int jobs_fini(void) {
    if(jtable==NULL)
        return -1;

    JOB_NODE *current_job = jtable->head->next;
    while(current_job != jtable->head)
    {
        if(jobs_poll(current_job->job_id) < 0){
            if(jobs_cancel(current_job->job_id) <0) return -1;
        }
        if(jobs_expunge(current_job->job_id) <0) return -1;
        current_job = current_job->next;
    }

    free(jtable->head);
    free(jtable);
    jtable = NULL;
    return 0;
}

/**
 * @brief  Print the current jobs table.
 * @details  This function is used to print the current contents of the jobs
 * table to a specified output stream.  The output should consist of one line
 * per existing job.  Each line should have the following format:
 *
 *    <jobid>\t<pgid>\t<status>\t<pipeline>
 *
 * where <jobid> is the numeric job ID of the job, <status> is one of the
 * following strings: "new", "running", "completed", "aborted", or "canceled",
 * and <pipeline> is the job's pipeline, as printed by function show_pipeline()
 * in the syntax module.  The \t stand for TAB characters.
 *
 * @param file  The output stream to which the job table is to be printed.
 * @return 0  If the jobs table was successfully printed, -1 otherwise.
 */
int jobs_show(FILE *file) {
    if(jtable == NULL)
        return -1;

    /* Iterate Job Table. */
    // char *s;
    JOB_NODE *current_job = jtable->head->next;
    while(current_job != jtable->head)
    {
        fprintf(file, "%d\t%d\t%s\t",
            current_job->job_id, (int)current_job->pgid, current_job->status);
        show_pipeline(file, current_job->pipeline);
        fprintf(file, "%c",'\n');
        current_job = current_job->next;

    }

    return 0;

}

/**
 * @brief  Create a new job to run a pipeline.
 * @details  This function creates a new job and starts it running a specified
 * pipeline.  The pipeline will consist of a "leader" process, which is the direct
 * child of the process that calls this function, plus one child of the leader
 * process to run each command in the pipeline.  All processes in the pipeline
 * should have a process group ID that is equal to the process ID of the leader.
 * The leader process should wait for all of its children to terminate before
 * terminating itself.  The leader should return the exit status of the process
 * running the last command in the pipeline as its own exit status, if that
 * process terminated normally.  If the last process terminated with a signal,
 * then the leader should terminate via SIGABRT.
 *
 * If the "capture_output" flag is set for the pipeline, then the standard output
 * of the last process in the pipeline should be redirected to be the same as
 * the standard output of the pipeline leader, and this output should go via a
 * pipe to the main Mush process, where it should be read and saved in the data
 * store as the value of a variable, as described in the assignment handout.
 * If "capture_output" is not set for the pipeline, but "output_file" is non-NULL,
 * then the standard output of the last process in the pipeline should be redirected
 * to the specified output file.   If "input_file" is set for the pipeline, then
 * the standard input of the process running the first command in the pipeline should
 * be redirected from the specified input file.
 *
 * @param pline  The pipeline to be run.  The jobs module expects this object
 * to be valid for as long as it requires, and it expects to be able to free this
 * object when it is finished with it.  This means that the caller should not pass
 * a pipeline object that is shared with any other data structure, but rather should
 * make a copy to be passed to this function.
 *
 * @return  -1 if the pipeline could not be initialized properly, otherwise the
 * value returned is the job ID assigned to the pipeline.
 */
int jobs_run(PIPELINE *pline) {
    /* If job table not initialized, return -1*/
    if(pline == NULL)
        return -1;

    sigset_t mask_all, prev_all;
    sigfillset(&mask_all);
    sigprocmask(SIG_BLOCK, &mask_all, &prev_all);

    int cofd[2];
    pipe(cofd);

    /* Create a the leader process. */
    pid_t pid;
    if((pid=fork())==0){
        /* Leader Process create a child process for each command.*/

        /* Set process group id. */
        if(setpgid(getpid(), getpid())<0) exit(EXIT_FAILURE);

        /* Create a pipeline. */
        int fd[2];
        int prev_input = STDIN_FILENO;
        /* Leader Process create a child process for each command.*/
        int exit_status;

        pid_t cpid;
        COMMAND *current_command  = pline->commands;
        while(current_command)
        {
            if(pipe(fd) < 0){
                exit(EXIT_FAILURE);
            }
            if((cpid=fork())==0)
            {
                /* Set process group id. */
                if(setpgid(getpid(), getppid())<0){
                    exit(EXIT_FAILURE);
                }
                /* Count the number of args.*/
                int argc = 0;
                ARG *current_arg = current_command->args;
                while(current_arg)
                {
                    argc++;
                    current_arg = current_arg->next;
                }

                /* Create argv. */
                current_arg = current_command->args;
                char **argv = (char **)malloc((argc+1)*sizeof(char *));
                for(int i=0; i<argc; i++)
                {
                    argv[i] = eval_to_string(current_arg->expr);
                    current_arg = current_arg->next;
                }
                argv[argc] = NULL;

                /* Redirect input. */
                if(current_command == pline->commands)
                {
                    // Process 1 redirect input from input file
                    if(pline->input_file){
                        int input_fd;
                        if((input_fd = open(pline->input_file, O_RDONLY)) < 0) exit(EXIT_FAILURE);
                        if(dup2(input_fd, STDIN_FILENO)<0) exit(EXIT_FAILURE);
                        if(close(input_fd)<0) exit(EXIT_FAILURE);
                    }
                }
                else{
                    // redirect input from fd[0]
                    if(prev_input != STDIN_FILENO)
                    {
                        if(dup2(prev_input, STDIN_FILENO)<0) exit(EXIT_FAILURE);
                        if(close(prev_input)<0) exit(EXIT_FAILURE);
                    }
                }

                /* Redirect output. */
                if(current_command->next == NULL){
                    // Process n redirect output to output file
                    if(pline->output_file){
                        int output_fd;
                        if((output_fd = open(pline->output_file, O_WRONLY)) < 0) exit(EXIT_FAILURE);
                        if(dup2(output_fd, STDOUT_FILENO)<0) exit(EXIT_FAILURE);
                        if(close(output_fd)<0) exit(EXIT_FAILURE);
                    }
                    else if(pline->capture_output){
                        if(dup2(cofd[1], STDOUT_FILENO)<0) exit(EXIT_FAILURE);
                    }
                }
                else{
                    // redirect output to fd[1]
                    if(dup2(fd[1], STDOUT_FILENO)<0) exit(EXIT_FAILURE);
                }
                if(close(fd[1])<0) exit(EXIT_FAILURE); //close write side;

                // output cap
                if(close(cofd[0])<0 || close(cofd[1])<0) exit(EXIT_FAILURE);
                /* Each child process execvp the command. */
                if(execvp(argv[0], argv)<0)
                {
                    perror("execvp failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                if(close(fd[1])<0) exit(EXIT_FAILURE);
                prev_input = fd[0];
            }
            current_command = current_command->next;
        }
        if(close(cofd[0])<0 || close(cofd[1])<0) exit(EXIT_FAILURE);
        while(wait(&exit_status)>0)
        {
            if(WEXITSTATUS(exit_status) != EXIT_SUCCESS){
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else{
        /* Main process add the leader process's pid to job table. */
        if(close(cofd[1])<0) exit(EXIT_FAILURE);

        if(pline->capture_output)
        {
            fcntl(cofd[0], F_SETFL, O_NONBLOCK);
            fcntl(cofd[0], F_SETFL, O_ASYNC);
            fcntl(cofd[0], F_SETOWN, getpid());
        }
        else{
            if(close(cofd[0])<0) exit(EXIT_FAILURE);
            cofd[0] = -1;
        }


        JOB_NODE *new_job = (JOB_NODE *) malloc(sizeof(JOB_NODE));
        new_job->job_id = jid++;
        new_job->pgid = pid;
        new_job->status = "new";
        new_job->exit_status = -1;
        new_job->readfd = cofd[0];
        new_job->pipeline = copy_pipeline(pline);
        new_job->job_output = NULL;

        /*Set the links. */
        jtable->head->prev->next = new_job;
        new_job->prev = jtable->head->prev;
        new_job->next = jtable->head;
        jtable->head->prev = new_job;


        new_job->status = "running";

        sigprocmask(SIG_SETMASK, &prev_all, NULL);

        return new_job->job_id;
    }

    return -1;

}

int change_job_status(pid_t pid, char *status, int exit_status){
    if(jtable == NULL)
        return -1;

    /* Find the job. */
    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        if(target->pgid == pid)
        {
            target->status = status;
            target->exit_status = exit_status;
            return 0;
        }
        target = target->next;
    }

    return -1;
}

/**
 * @brief  Wait for a job to terminate.
 * @details  This function is used to wait for the job with a specified job ID
 * to terminate.  A job has terminated when it has entered the COMPLETED, ABORTED,
 * or CANCELED state.
 *
 * @param  jobid  The job ID of the job to wait for.
 * @return  the exit status of the job leader, as returned by waitpid(),
 * or -1 if any error occurs that makes it impossible to wait for the specified job.
 */
int jobs_wait(int jobid) {
    if(jtable == NULL)
        return -1;

    sigset_t new_mask;
    sigfillset(&new_mask);
    sigdelset(&new_mask, SIGCHLD);

    //int status;
    /* Find the job. */
    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        if(target->job_id == jobid)
        {
            // if(waitpid(target->pgid, &status, 0) < 0)
            //     return -1;

            // if(WIFSTOPPED(status)|WIFSIGNALED(status)|WIFEXITED(status))
            // {
            //     return status;
            // }
            // return -1;
            while(1){
                if( (strcmp(target->status, "completed") == 0)
                    || (strcmp(target->status, "aborted") == 0)
                    || (strcmp(target->status, "canceled") == 0))
                {
                    return target->exit_status;
                }
                sigsuspend(&new_mask);
            }
        }
        target = target->next;
    }

    return -1;

}

/**
 * @brief  Poll to find out if a job has terminated.
 * @details  This function is used to poll whether the job with the specified ID
 * has terminated.  This is similar to jobs_wait(), except that this function returns
 * immediately without waiting if the job has not yet terminated.
 *
 * @param  jobid  The job ID of the job to wait for.
 * @return  the exit status of the job leader, as returned by waitpid(), if the job
 * has terminated, or -1 if the job has not yet terminated or if any other error occurs.
 */
int jobs_poll(int jobid) {
    if(jtable == NULL)
        return -1;

    //int status;
    /* Find the job. */
    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        if(target->job_id == jobid)
        {
            // if(waitpid(target->pgid, &status, WNOHANG) < 0)
            //     return -1;
            // if(WIFSTOPPED(status)|WIFSIGNALED(status)|WIFEXITED(status))
            //     return status;
            // return -1;
            if( (strcmp(target->status, "completed") == 0)
                || (strcmp(target->status, "aborted") == 0)
                || (strcmp(target->status, "canceled") == 0))
            {
                return target->exit_status;
            }
            return -1;
        }
        target = target->next;
    }

    return -1;
}

/**
 * @brief  Expunge a terminated job from the jobs table.
 * @details  This function is used to expunge (remove) a job that has terminated from
 * the jobs table, so that space in the table can be used to start some new job.
 * In order to be expunged, a job must have terminated; if an attempt is made to expunge
 * a job that has not yet terminated, it is an error.  Any resources (exit status,
 * open pipes, captured output, etc.) that were being used by the job are finalized
 * and/or freed and will no longer be available.
 *
 * @param  jobid  The job ID of the job to expunge.
 * @return  0 if the job was successfully expunged, -1 if the job could not be expunged.
 */
int jobs_expunge(int jobid) {
    if(jobs_poll(jobid) == -1)
        return -1;

    /* Find the job. */
    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        if(target->job_id == jobid)
        {
            // Remove the job from table by unlink
            target->prev->next = target->next;
            target->next->prev = target->prev;
            target->prev = NULL;
            target->next = NULL;

            // free the job node
            if(target->pipeline) free_pipeline(target->pipeline);
            if(target->job_output) free(target->job_output);
            if(target->readfd != -1){
                if(close(target->readfd)<0) exit(EXIT_FAILURE);
            }
            free(target);

            return 0;
        }
        target = target->next;
    }

    return -1;
}

/**
 * @brief  Attempt to cancel a job.
 * @details  This function is used to attempt to cancel a running job.
 * In order to be canceled, the job must not yet have terminated and there
 * must not have been any previous attempt to cancel the job.
 * Cancellation is attempted by sending SIGKILL to the process group associated
 * with the job.  Cancellation becomes successful, and the job actually enters the canceled
 * state, at such subsequent time as the job leader terminates as a result of SIGKILL.
 * If after attempting cancellation, the job leader terminates other than as a result
 * of SIGKILL, then cancellation is not successful and the state of the job is either
 * COMPLETED or ABORTED, depending on how the job leader terminated.
 *
 * @param  jobid  The job ID of the job to cancel.
 * @return  0 if cancellation was successfully initiated, -1 if the job was already
 * terminated, a previous attempt had been made to cancel the job, or any other
 * error occurred.
 */
int jobs_cancel(int jobid) {
    if(jobs_poll(jobid) != -1)
        return -1;
    /* Find the job. */
    JOB_NODE *target = jtable->head->next;
    while(target != jtable->head)
    {
        if(target->job_id == jobid)
        {
            // Cancell the job
            if(kill(-(target->pgid),SIGKILL)<0)
            {
                return -1;
            }
            return 0;
        }
        target = target->next;
    }

    return -1;
}

/**
 * @brief  Get the captured output of a job.
 * @details  This function is used to retrieve output that was captured from a job
 * that has terminated, but that has not yet been expunged.  Output is captured for a job
 * when the "capture_output" flag is set for its pipeline.
 *
 * @param  jobid  The job ID of the job for which captured output is to be retrieved.
 * @return  The captured output, if the job has terminated and there is captured
 * output available, otherwise NULL.
 */
char *jobs_get_output(int jobid) {
    if(jtable == NULL)
        return NULL;

    JOB_NODE *current_job = jtable->head->next;
    while(current_job != jtable->head)
    {
        if(current_job->job_id == jobid)
        {
            return current_job->job_output;
        }
        current_job=current_job->next;
    }
    return NULL;
}

/**
 * @brief  Pause waiting for a signal indicating a potential job status change.
 * @details  When this function is called it blocks until some signal has been
 * received, at which point the function returns.  It is used to wait for a
 * potential job status change without consuming excessive amounts of CPU time.
 *
 * @return -1 if any error occurred, 0 otherwise.
 */
int jobs_pause(void) {
    pause();
    return 0;
}
