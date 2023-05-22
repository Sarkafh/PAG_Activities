/*******************************************************************************
* Title                 :   queue
* Filename              :   queue.c
* Author                :   Gabriel Tomio
* Origin Date           :   24/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "queue_public.h"
#include "queue_private.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/** ****************************************************************************
* Function : queue_create(pp_queue_t pp_queue, int type_size, int num_of_elements)
* @scope: Public
* @description: Initilizes the generic queue
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_create(pp_queue_t pp_queue, int type_size, int num_of_elements)
{
    if((num_of_elements <= 0)||(type_size <= 0))
    {
        // printf("Invalid initialization parameters!\n");
        return QUEUE_ERROR;
    }

    (*pp_queue) = (p_queue_t)malloc(sizeof(queue_priv_t));

    if ((*pp_queue) == NULL)
    {
        // printf("Memory could not be allocated!\n");
        return QUEUE_ERROR;
    }

    (*pp_queue)->p_data = (void*)malloc(num_of_elements*type_size);

    if ((*pp_queue)->p_data == NULL)
    {
        free((*pp_queue));
        // printf("Memory could not be allocated!\n");
        return QUEUE_ERROR;
    }

    (*pp_queue)->num_of_elements = num_of_elements;
    (*pp_queue)->type_size = type_size;
    (*pp_queue)->start_index = 0;
    (*pp_queue)->current_size = 0;
    
    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_destroy(pp_queue_t pp_queue)
* @scope: Public
* @description: Frees the allocated memory
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_destroy(pp_queue_t pp_queue)
{
    if ((*pp_queue) == NULL)
    {
        return QUEUE_ERROR;
    }

    free((*pp_queue)->p_data);
    free(*pp_queue);

    (*pp_queue) = NULL;

    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_enqueue(p_queue_t p_queue, void * p_queue_data)
* @scope: Public
* @description: Add a new element in the queue
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_enqueue(p_queue_t p_queue, void * p_queue_data)
{
    if (p_queue == NULL)
    {
        return QUEUE_ERROR;
    }

    void * p_data_temp;
    int new_data_offset;

    if (queue_is_full(p_queue) == QUEUE_IS_FULL)
    {
        // printf("The queue is already full!\n");
        return QUEUE_ERROR;
    }

    new_data_offset = (p_queue->start_index + p_queue->current_size) % p_queue->num_of_elements;
    p_data_temp = p_queue->p_data + new_data_offset * p_queue->type_size;

    p_queue->current_size++;

    memcpy(p_data_temp, p_queue_data, p_queue->type_size);
    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_dequeue(p_queue_t p_queue, void * p_queue_data)
* @scope: Public
* @description: Deletes the queue front element
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_dequeue(p_queue_t p_queue, void * p_queue_data)
{
    if (p_queue == NULL)
    {
        return QUEUE_ERROR;
    }
    
    void * p_data_temp;

    if (queue_is_empty(p_queue) == QUEUE_IS_EMPTY)
    {
        // printf("No data to be output, queue is empty!\n");
        return QUEUE_ERROR;
    }

    p_data_temp = p_queue->p_data + p_queue->start_index * p_queue->type_size;
    memcpy(p_queue_data, p_data_temp, p_queue->type_size);

    p_queue->current_size --;
    p_queue->start_index = (p_queue->start_index == p_queue->num_of_elements-1) ? 0 : p_queue->start_index + 1;

    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_front(p_queue_t p_queue, void * p_queue_data)
* @scope: Public
* @description: Writes the front value on the address pointed by p_queue_data
*               without removing it
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_front(p_queue_t p_queue, void * p_queue_data)
{
    if (p_queue == NULL)
    {
        return QUEUE_ERROR;
    }

    void * p_data_temp;

    if((queue_is_empty(p_queue) == QUEUE_IS_EMPTY))
    {
        // printf("No data to be output, queue is empty!\n");
        return QUEUE_ERROR;
    }

    p_data_temp = p_queue->p_data + p_queue->start_index * p_queue->type_size;
    memcpy(p_queue_data, p_data_temp, p_queue->type_size);

    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_is_full(p_queue_t p_queue)
* @scope: Private
* @description: Checks if queue is full
* @return 		QUEUE_IS_FULL -> QUEUE is full
                QUEUE_IS_NOT_FULL -> QUEUE is not full
*******************************************************************************/
int queue_is_full(p_queue_t p_queue)
{
    if(p_queue->current_size >= p_queue->num_of_elements)
    {
        return QUEUE_IS_FULL;
    }
    return QUEUE_IS_NOT_FULL;
}

/** ****************************************************************************
* Function : queue_is_empty(p_queue_t p_queue)
* @scope: Private
* @description: Checks if queue is empty
* @return 		QUEUE_IS_EMPTY -> QUEUE is empty
                QUEUE_IS_NOT_EMPTY -> QUEUE is not empty
*******************************************************************************/
int queue_is_empty(p_queue_t p_queue)
{
    if(p_queue->current_size == 0)
    {
        return QUEUE_IS_EMPTY;
    }
    return QUEUE_IS_NOT_EMPTY;
}

/** ****************************************************************************
* Function : queue_capacity(p_queue_t p_queue, int * capacity)
* @scope: Public
* @description: Returns the allocated capacity of the queue
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_capacity(p_queue_t p_queue, int * capacity)
{
    if (p_queue == NULL)
    {
        return QUEUE_ERROR;
    }

    *capacity = p_queue->num_of_elements; 

    return QUEUE_SUCCESS;
}

/** ****************************************************************************
* Function : queue_current_size(p_queue_t p_queue, int * current_size)
* @scope: Public
* @description: Returns the current size of the queue
* @return 		QUEUE_ERROR -> Finished execution with error
                QUEUE_SUCCESS -> Finished execution with success
*******************************************************************************/
int queue_current_size(p_queue_t p_queue, int * current_size)
{
    if (p_queue == NULL)
    {
        return QUEUE_ERROR;
    }

    *current_size = p_queue->current_size; 

    return QUEUE_SUCCESS;
}
/*************** END OF FUNCTIONS ***************************************************************************/