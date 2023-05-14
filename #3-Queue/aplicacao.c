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


/** ****************************************************************************
* Function : main(int argc, char **argv)
* @description: gets the towers from an input file and reorders them
* @return 		FINISHED_ERROR -> finished operation with error
                FINISHED_SUCCESS -> finished operation successfully
*******************************************************************************/
#define QUEUE_SIZE  10
int main(int argc, char **argv)
{
    int numero = 0;
    p_queue_t fila_gen = NULL;

    queue_create(&fila_gen, sizeof(int), UNLIMITED_SIZE_QUEUE);

    for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
        numero = i;
        queue_enqueue(fila_gen, (void *)&numero);
        printf("Enfileirar: %d\n", numero);
    }

    printf("\n");

    for (size_t i = 0; i < QUEUE_SIZE/2; i++)
    {
        queue_dequeue(fila_gen, (void *)&numero);
        printf("Desenfileirar: %d\n", numero);
    }

    printf("\n");

    for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
        numero = 15*(i+1);
        if(queue_enqueue(fila_gen, (void *)&numero) != QUEUE_ERROR)
        {
            printf("Enfileirar: %d\n", numero);
        }
    }

    printf("\n");

    for (size_t i = 0; i < QUEUE_SIZE + QUEUE_SIZE/2 +10; i++)
    {
        if(queue_dequeue(fila_gen, (void *)&numero) != QUEUE_ERROR)
        {
            printf("Desenfileirar: %d\n", numero);
        }
    }

    queue_destroy(&fila_gen);
    
    return FINISHED_SUCCESS;
}

/*************** END OF FUNCTIONS ***************************************************************************/