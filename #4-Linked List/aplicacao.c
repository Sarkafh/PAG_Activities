/*******************************************************************************
* Title                 :   aplicacao  
* Filename              :   aplicacao.c
* Author                :   Gabriel Tomio
* Origin Date           :   01/05/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   Game of Towers
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "aplicacao.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/
void print_int(void * p_data)
{
    int * value = (int *) p_data;
    printf("%d\n", *value);
}

void free_int(void * p_data)
{
    int * value = (int *) p_data;
    free(value);
}

int increasing_order(void * p_new_data, void * p_stored_data)
{
    int * new_value = (int *) p_new_data;
    int * stored_value = (int *) p_stored_data;
    return(*new_value < *stored_value); // todo checar o sinal
}

int decreasing_order(void * p_new_data, void * p_stored_data)
{
    int * new_value = (int *) p_new_data;
    int * stored_value = (int *) p_stored_data;
    return(*new_value > *stored_value); // todo checar o sinal
}

/** ****************************************************************************
* Function : main(int argc, char **argv)
* @description: gets the towers from an input file and reorders them
* @return 		FINISHED_ERROR -> finished operation with error
                FINISHED_SUCCESS -> finished operation successfully
*******************************************************************************/
int main(int argc, char **argv)
{
    p_linked_list_t my_linked_list;

    char line[MAXIMUM_SIZE_OF_LINE];
    char * p_new_line;
    int new_data;

    linked_list_create(&my_linked_list, sizeof(int), free_int);

    while (fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL)
    {
        p_new_line = strtok(line, DELIMITER_CHARACTER);
        while ((p_new_line != NULL) && (strcmp(p_new_line, "\n") != 0))
        {
            p_new_line = strtok(NULL, DELIMITER_CHARACTER);
            new_data = atoi(p_new_line);
            linked_list_ordered_insert(my_linked_list, (void*) &new_data, increasing_order);
        }
    }

    int i = 0;

    while (!linked_list_print(my_linked_list, print_int, i))
    {
        i++;
    }
    
    linked_list_destroy(&my_linked_list);

    return FINISHED_SUCCESS;
}
/*************** END OF FUNCTIONS ***************************************************************************/