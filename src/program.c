#include <stdlib.h>
#include <stdio.h>

#include "mush.h"
#include "debug.h"

/*
 * This is the "program store" module for Mush.
 * It maintains a set of numbered statements, along with a "program counter"
 * that indicates the current point of execution, which is either before all
 * statements, after all statements, or in between two statements.
 * There should be no fixed limit on the number of statements that the program
 * store can hold.
 */
typedef struct prog_line{
    struct prog_line *prev;
    struct prog_line *next;
    STMT *content;
}PROG_LINE;

typedef struct prog_store{
    PROG_LINE *head;
    PROG_LINE *counter;
}PROG_STORE;

PROG_STORE *pstorage = NULL;

/**
 * @brief  Output a listing of the current contents of the program store.
 * @details  This function outputs a listing of the current contents of the
 * program store.  Statements are listed in increasing order of their line
 * number.  The current position of the program counter is indicated by
 * a line containing only the string "-->" at the current program counter
 * position.
 *
 * @param out  The stream to which to output the listing.
 * @return  0 if successful, -1 if any error occurred.
 */
int prog_list(FILE *out) {
    /* The Program Store is empty. */
    if(pstorage == NULL)
    {
        return 0;
    }

    /* Iterate Program Store. */
    PROG_LINE *current_line = pstorage->head->next;
    while(current_line != pstorage->head)
    {
        if(current_line == pstorage->counter)
        {
            if(fprintf(out, "-->\n") < 0){
                return -1;
            }
        }
        if(current_line->content != NULL)
        {
            show_stmt(out, current_line->content);
        }
        current_line = current_line->next;
    }
    if(current_line == pstorage->counter)
    {
        if(fprintf(out, "-->\n") < 0){
            return -1;
        }
    }

    return 0;
}

/**
 * @brief  Insert a new statement into the program store.
 * @details  This function inserts a new statement into the program store.
 * The statement must have a line number.  If the line number is the same as
 * that of an existing statement, that statement is replaced.
 * The program store assumes the responsibility for ultimately freeing any
 * statement that is inserted using this function.
 * Insertion of new statements preserves the value of the program counter:
 * if the position of the program counter was just before a particular statement
 * before insertion of a new statement, it will still be before that statement
 * after insertion, and if the position of the program counter was after all
 * statements before insertion of a new statement, then it will still be after
 * all statements after insertion.
 *
 * @param stmt  The statement to be inserted.
 * @return  0 if successful, -1 if any error occurred.
 */
int prog_insert(STMT *stmt) {

    /* Initialize program store. */
    if(pstorage == NULL){
        pstorage = (PROG_STORE *) malloc(sizeof(PROG_STORE));
        /* Set dummy head and dummy tail, and counter to the dummy head. */
        PROG_LINE *dummy_head = (PROG_LINE *) malloc(sizeof(PROG_LINE));
        pstorage->head = dummy_head;
        pstorage->counter = NULL;

        /* Link head to head. */
        pstorage->head->prev = dummy_head;
        pstorage->head->next = dummy_head;
        pstorage->head->content = NULL;
    }

    /* If statement has no line number, return -1*/
    if(stmt->lineno <=0)
        return -1;

    /* Iterate Program Store. */
    PROG_LINE *current_line = pstorage->head->next;
    while(current_line != pstorage->head)
    {
        /* If find a same line number, then replace it and return. */
        if(current_line->content->lineno == stmt->lineno)
        {
            free_stmt(current_line->content);
            current_line->content = stmt;
            return 0;

        }
        /* If find a larger line number, then break. */
        if(current_line->content->lineno > stmt->lineno)
        {
            break;
        }
        current_line = current_line->next;
    }

    /* Create new line node with the statement.*/
    PROG_LINE *new_line = (PROG_LINE *) malloc(sizeof(PROG_LINE));
    new_line->content = stmt;

    /* Insert as prev of current_line.*/
    current_line->prev->next = new_line;
    new_line->prev = current_line->prev;
    new_line->next = current_line;
    current_line->prev = new_line;

    return 0;
}

/**
 * @brief  Delete statements from the program store.
 * @details  This function deletes from the program store statements whose
 * line numbers fall in a specified range.  Any deleted statements are freed.
 * Deletion of statements preserves the value of the program counter:
 * if before deletion the program counter pointed to a position just before
 * a statement that was not among those to be deleted, then after deletion the
 * program counter will still point the position just before that same statement.
 * If before deletion the program counter pointed to a position just before
 * a statement that was among those to be deleted, then after deletion the
 * program counter will point to the first statement beyond those deleted,
 * if such a statement exists, otherwise the program counter will point to
 * the end of the program.
 *
 * @param min  Lower end of the range of line numbers to be deleted.
 * @param max  Upper end of the range of line numbers to be deleted.
 */
int prog_delete(int min, int max) {

    /* Validate min and max.*/
    if(min <= 0 || max <= 0 || max < min)
        return -1;

    /* The Program Store is empty. */
    if(pstorage == NULL)
        return 0;

    /* Iterate Program Store. */
    PROG_LINE *remove_line = NULL;
    PROG_LINE *current_line = pstorage->head->next;
    while(current_line != pstorage->head)
    {
        /* If the line is within the delete range. */
        if(current_line->content->lineno >= min && current_line->content->lineno <= max)
        {
            /* If current_line is the counter that need to be remove, then set counter to next. */
            if(current_line == pstorage->counter)
            {
                pstorage->counter = current_line->next;
            }
            /* Set remove line to current_line. */
            remove_line = current_line;
            /* Set current_line to next. */
            current_line = current_line->next;

            /*Delete the remove line.*/
            remove_line->prev->next = remove_line->next;
            remove_line->next->prev = remove_line->prev;
            remove_line->prev = NULL;
            remove_line->next = NULL;

            /* Free the statement. */
            free_stmt(remove_line->content);
            remove_line->content = NULL;
            /* Free the line. */
            free(remove_line);
        }
        else
        {
            /* Set current_line to next. */
            current_line = current_line->next;
        }
    }
    return 0;
}

/**
 * @brief  Reset the program counter to the beginning of the program.
 * @details  This function resets the program counter to point just
 * before the first statement in the program.
 */
void prog_reset(void) {
    /* The Program Store is empty. */
    if(pstorage == NULL)
        return;
    pstorage->counter = pstorage->head->next;
    return;
}

/**
 * @brief  Fetch the next program statement.
 * @details  This function fetches and returns the first program
 * statement after the current program counter position.  The program
 * counter position is not modified.  The returned pointer should not
 * be used after any subsequent call to prog_delete that deletes the
 * statement from the program store.
 *
 * @return  The first program statement after the current program
 * counter position, if any, otherwise NULL.
 */
STMT *prog_fetch(void) {
    /* The Program Store is empty. */
    if(pstorage == NULL)
        return NULL;
    return pstorage->counter->content;
}

/**
 * @brief  Advance the program counter to the next existing statement.
 * @details  This function advances the program counter by one statement
 * from its original position and returns the statement just after the
 * new position.  The returned pointer should not be used after any
 * subsequent call to prog_delete that deletes the statement from the
 * program store.
 *
 * @return The first program statement after the new program counter
 * position, if any, otherwise NULL.
 */
STMT *prog_next() {
    /* The Program Store is empty. */
    if(pstorage == NULL)
        return NULL;

    if(pstorage->counter == NULL)
        return NULL;

    /* If program counter is not at the end, then advance the counter. */
    if(pstorage->counter != pstorage->head)
        pstorage->counter = pstorage->counter->next;

    return pstorage->counter->content;
}

/**
 * @brief  Perform a "go to" operation on the program store.
 * @details  This function performs a "go to" operation on the program
 * store, by resetting the program counter to point to the position just
 * before the statement with the specified line number.
 * The statement pointed at by the new program counter is returned.
 * If there is no statement with the specified line number, then no
 * change is made to the program counter and NULL is returned.
 * Any returned statement should only be regarded as valid as long
 * as no calls to prog_delete are made that delete that statement from
 * the program store.
 *
 * @return  The statement having the specified line number, if such a
 * statement exists, otherwise NULL.
 */
STMT *prog_goto(int lineno) {

    /* Iterate Program Store. */
    PROG_LINE *current_line = pstorage->head->next;
    while(current_line != pstorage->head)
    {
        if(current_line->content->lineno == lineno)
        {
            pstorage->counter = current_line;
            return pstorage->counter->content;
        }
        current_line = current_line->next;
    }

    return NULL;
}
