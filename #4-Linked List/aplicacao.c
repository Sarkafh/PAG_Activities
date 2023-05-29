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
    printf("Init Dado: %d\n", *value);
}

void print_int2(void * p_data)
{
    int * value = (int *) p_data;
    printf("After Dado: %d\n", *value);
}

void free_int(void * p_data)
{
    int * value = (int *) p_data;
    free(value);
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
    int value = 1;

    linked_list_create(&my_linked_list, sizeof(int), free_int);

    for (int i = 0; i < 10; i++)
    {
        linked_list_insert(my_linked_list, &value, i);
        value++;
    }
    value = 50;
    linked_list_insert(my_linked_list, &value, 1);

    for (int i = 0; i < 11; i++)
    {
        linked_list_print(my_linked_list, print_int, i);
    }

    for (int i = 5; i > 0; i--)
    {
        linked_list_remove(my_linked_list, &value, i*2);
    }

    for (int i = 0; i < 11-5; i++)
    {
        linked_list_print(my_linked_list, print_int2, i);
    }

    linked_list_destroy(&my_linked_list);
    return FINISHED_SUCCESS;
}
/*************** END OF FUNCTIONS ***************************************************************************/