#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This is the "data store" module for Mush.
 * It maintains a mapping from variable names to values.
 * The values of variables are stored as strings.
 * However, the module provides functions for setting and retrieving
 * the value of a variable as an integer.  Setting a variable to
 * an integer value causes the value of the variable to be set to
 * a string representation of that integer.  Retrieving the value of
 * a variable as an integer is possible if the current value of the
 * variable is the string representation of an integer.
 */

typedef struct var_node{
    struct var_node *prev;
    struct var_node *next;
    char *var_name;
    char *var_value;
}VAR_NODE;

typedef struct var_store{
    VAR_NODE *head;
}VAR_STORE;

VAR_STORE *vstorage = NULL;

/**
 * @brief  Get the current value of a variable as a string.
 * @details  This function retrieves the current value of a variable
 * as a string.  If the variable has no value, then NULL is returned.
 * Any string returned remains "owned" by the data store module;
 * the caller should not attempt to free the string or to use it
 * after any subsequent call that would modify the value of the variable
 * whose value was retrieved.  If the caller needs to use the string for
 * an indefinite period, a copy should be made immediately.
 *
 * @param  var  The variable whose value is to be retrieved.
 * @return  A string that is the current value of the variable, if any,
 * otherwise NULL.
 */
char *store_get_string(char *var) {
    /* The data store is empty, return NULL. */
    if(vstorage == NULL)
        return NULL;

    /* Iterate the vstorage. */
    VAR_NODE *current_variable = vstorage->head->next;
    while(current_variable != vstorage->head)
    {
        /* If find a same variable name, return its value. */
        if(strcmp(var, current_variable->var_name) == 0)
        {
            return current_variable->var_value;
        }
        current_variable = current_variable->next;
    }

    /* Not find same variable name, return NULL. */
    return NULL;
}

/**
 * @brief  Get the current value of a variable as an integer.
 * @details  This retrieves the current value of a variable and
 * attempts to interpret it as an integer.  If this is possible,
 * then the integer value is stored at the pointer provided by
 * the caller.
 *
 * @param  var  The variable whose value is to be retrieved.
 * @param  valp  Pointer at which the returned value is to be stored.
 * @return  If the specified variable has no value or the value
 * cannot be interpreted as an integer, then -1 is returned,
 * otherwise 0 is returned.
 */
int store_get_int(char *var, long *valp) {
    if(vstorage == NULL)
        return -1;

    long result;
    char *end_ptr;
    VAR_NODE *current_variable = vstorage->head->next;
    while(current_variable != vstorage->head)
    {
        if(strcmp(var, current_variable->var_name) == 0)
        {
            if(current_variable->var_value == NULL || *(current_variable->var_value) == 0)
            {
                return -1;
            }
            result = strtol(current_variable->var_value, &end_ptr, 10);
            if(*end_ptr == 0)
            {
                *valp = result;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        current_variable = current_variable->next;
    }

    return -1;
}

/**
 * @brief  Set the value of a variable as a string.
 * @details  This function sets the current value of a specified
 * variable to be a specified string.  If the variable already
 * has a value, then that value is replaced.  If the specified
 * value is NULL, then any existing value of the variable is removed
 * and the variable becomes un-set.  Ownership of the variable and
 * the value strings is not transferred to the data store module as
 * a result of this call; the data store module makes such copies of
 * these strings as it may require.
 *
 * @param  var  The variable whose value is to be set.
 * @param  val  The value to set, or NULL if the variable is to become
 * un-set.
 */
int store_set_string(char *var, char *val) {

    /* If var name is NULL, return -1. */
    if(var == NULL)
        return -1;

    /* Initialize vstorage.*/
    if(vstorage==NULL)
    {
        vstorage = (VAR_STORE *) malloc(sizeof(VAR_STORE));
        /* Set a dummy head. */
        VAR_NODE *dummy_head = (VAR_NODE *) malloc(sizeof(VAR_NODE));
        vstorage->head = dummy_head;
        vstorage->head->next = dummy_head;
        vstorage->head->prev = dummy_head;
    }

    int len;
    char *varcpy, *valcpy;
    /* Iterate vstorage. */
    VAR_NODE *current_variable = vstorage->head->next;
    while(current_variable != vstorage->head)
    {
        /* If find the variable with same name. */
        if(strcmp(var, current_variable->var_name) == 0)
        {
            if(current_variable->var_value != NULL)
            {
                free(current_variable->var_value);
            }

            if(val == NULL)
            {
                valcpy = NULL;
            }
            else
            {
                /* Make a string copy of val. */
                len = strlen(val) + 1; // + 1 for '\0'
                valcpy = (char *) malloc(len*sizeof(char));
                strncpy(valcpy, val, len);
            }
            current_variable->var_value = valcpy;
            return 0;

        }
        current_variable = current_variable->next;
    }

    /* If not find same variable name, make copy of both var and val. */
    len = strlen(var) + 1; // + 1 for '\0'
    varcpy = (char *) malloc(len*sizeof(char));
    strncpy(varcpy, var, len);

    if(val == NULL)
    {
        valcpy = NULL;
    }
    else
    {
        /* Make a string copy of val. */
        len = strlen(val) + 1; // + 1 for '\0'
        valcpy = (char *) malloc(len*sizeof(char));
        strncpy(valcpy, val, len);
    }

    VAR_NODE *new_variable = (VAR_NODE *) malloc(sizeof(VAR_NODE));
    new_variable->var_name = varcpy;
    new_variable->var_value = valcpy;

    /* Insert the node . */
    current_variable->prev->next = new_variable;
    new_variable->prev = current_variable->prev;
    new_variable->next = current_variable;
    current_variable->prev = new_variable;

    return 0;
}

/**
 * @brief  Set the value of a variable as an integer.
 * @details  This function sets the current value of a specified
 * variable to be a specified integer.  If the variable already
 * has a value, then that value is replaced.  Ownership of the variable
 * string is not transferred to the data store module as a result of
 * this call; the data store module makes such copies of this string
 * as it may require.
 *
 * @param  var  The variable whose value is to be set.
 * @param  val  The value to set.
 */
int store_set_int(char *var, long val) {

    /* If var name is NULL, return -1. */
    if(var == NULL)
        return -1;

    /* Initialize vstorage.*/
    if(vstorage==NULL)
    {
        vstorage = (VAR_STORE *) malloc(sizeof(VAR_STORE));
        /* Set a dummy head. */
        VAR_NODE *dummy_head = (VAR_NODE *) malloc(sizeof(VAR_NODE));
        vstorage->head = dummy_head;
        vstorage->head->next = dummy_head;
        vstorage->head->prev = dummy_head;
    }

    int len;
    long tempval;
    char *varcpy, *valcpy;
    /* Iterate vstorage. */
    VAR_NODE *current_variable = vstorage->head->next;
    while(current_variable != vstorage->head)
    {
        /* If find the variable with same name. */
        if(strcmp(var, current_variable->var_name) == 0)
        {
            if(current_variable->var_value != NULL)
            {
                free(current_variable->var_value);
            }

            /* Make a string copy of val. */

            /* Count the long length. */
            tempval = val;
            if(val == 0){
                len = 1;
                tempval = val;
            }
            else if(val < 0)
            {
                len = 1;
                tempval = -val;
            }
            else
            {
                len = 0;
                tempval = val;
            }
            while(tempval != 0)
            {
                len++;
                tempval = tempval/10;
            }
            /* Count the long length. */
            len++; // for '\0'
            valcpy = (char *) malloc(len*sizeof(char));
            if(sprintf(valcpy, "%ld%c", val, '\0') != len){
                return -1;
            }

            current_variable->var_value = valcpy;
            return 0;

        }
        current_variable = current_variable->next;
    }

    /* If not find same variable name, make copy of both var and val. */
    len = strlen(var);
    len++;
    varcpy = (char *) malloc(len*sizeof(char));
    strncpy(varcpy, var, len);

    /* Make a string copy of val. */

    /* Count the long length. */
    tempval = val;
    if(val == 0){
        len = 1;
        tempval = val;
    }
    else if(val < 0)
    {
        len = 1;
        tempval = -val;
    }
    else
    {
        len = 0;
        tempval = val;
    }
    while(tempval != 0)
    {
        len++;
        tempval = tempval/10;
    }
    /* Count the long length. */
    len++; // for '\0'
    valcpy = (char *) malloc(len*sizeof(char));
    if(sprintf(valcpy, "%ld%c", val, '\0') != len){
        return -1;
    }

    VAR_NODE *new_variable = (VAR_NODE *) malloc(sizeof(VAR_NODE));
    new_variable->var_name = varcpy;
    new_variable->var_value = valcpy;

    /* Insert the node . */
    current_variable->prev->next = new_variable;
    new_variable->prev = current_variable->prev;
    new_variable->next = current_variable;
    current_variable->prev = new_variable;

    return 0;
}

/**
 * @brief  Print the current contents of the data store.
 * @details  This function prints the current contents of the data store
 * to the specified output stream.  The format is not specified; this
 * function is intended to be used for debugging purposes.
 *
 * @param f  The stream to which the store contents are to be printed.
 */
void store_show(FILE *f) {

    if(vstorage == NULL)
    {
        fprintf(f, "{}");
        return;
    }

    VAR_NODE *current_variable = vstorage->head->next;
    fprintf(f, "{");
    while(current_variable != vstorage->head)
    {
        if(current_variable->var_value == NULL){
            fprintf(f, "%s ", current_variable->var_name);
        }
        else{
            fprintf(f, "%s=%s", current_variable->var_name, current_variable->var_value);
        }
        if(current_variable->next != vstorage->head){
            fprintf(f, ", ");
        }
        current_variable = current_variable->next;
    }
    fprintf(f, "}");

    return;
}
