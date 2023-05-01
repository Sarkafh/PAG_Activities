/*******************************************************************************
* Title                 :   stack
* Filename              :   stack.c
* Author                :   Gabriel Tomio
* Origin Date           :   24/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "stack_public.h"
#include "stack_private.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/** ****************************************************************************
* Function : stack_create(pp_stack_t pp_stack, int type_size, int num_of_elements)
* @scope: Public
* @description: Initilizes the generic stack
* @return 		STACK_ERROR -> Finished execution with error
                STACK_SUCCESS -> Finished execution with success
*******************************************************************************/
int stack_create(pp_stack_t pp_stack, int type_size, int num_of_elements)
{
    (*pp_stack) = (p_stack_t)malloc(sizeof(stack_priv_t));

    if ((*pp_stack) == NULL)
    {
        printf("Memory could not be allocated!\n");
        return STACK_ERROR;
    }

    if((num_of_elements <= 0)||(type_size <= 0))
    {
        printf("Invalid initialization parameters!\n");
        return STACK_ERROR;
    }

    (*pp_stack)->top_index = EMPTY_STACK_INDEX;
    (*pp_stack)->num_of_elements = num_of_elements;
    (*pp_stack)->type_size = type_size;
    (*pp_stack)->p_data = (void*)malloc(num_of_elements*type_size);
    
    return STACK_SUCCESS;
}

/** ****************************************************************************
* Function : stack_destroy(pp_stack_t pp_stack)
* @scope: Public
* @description: Frees the allocated memory
* @return 		STACK_ERROR -> Finished execution with error
                STACK_SUCCESS -> Finished execution with success
*******************************************************************************/
int stack_destroy(pp_stack_t pp_stack)
{
    free((*pp_stack)->p_data);
    free(*pp_stack);
    return STACK_SUCCESS;
}

/** ****************************************************************************
* Function : stack_push(p_stack_t p_stack, void * p_stack_data)
* @scope: Public
* @description: Add a new element in the stack
* @return 		STACK_ERROR -> Finished execution with error
                STACK_SUCCESS -> Finished execution with success
*******************************************************************************/
int stack_push(p_stack_t p_stack, void * p_stack_data)
{
    if (stack_is_full(p_stack) == STACK_IS_NOT_FULL)
    {
        void * p_data_temp;

        p_stack->top_index++;
        p_data_temp = p_stack->p_data + p_stack->top_index * p_stack->type_size;
        memcpy(p_data_temp, p_stack_data, p_stack->type_size);
        return STACK_SUCCESS;
    }
    // printf("The stack is already full!\n");
    return STACK_ERROR;
}

/** ****************************************************************************
* Function : stack_pop(p_stack_t p_stack, void * p_stack_data)
* @scope: Public
* @description: Deletes the stack top element
* @return 		STACK_ERROR -> Finished execution with error
                STACK_SUCCESS -> Finished execution with success
*******************************************************************************/
int stack_pop(p_stack_t p_stack, void * p_stack_data)
{
    if (stack_is_empty(p_stack) == STACK_IS_NOT_EMPTY)
    {
        void * p_data_temp;

        p_data_temp = p_stack->p_data + p_stack->top_index * p_stack->type_size;
        memcpy(p_stack_data, p_data_temp, p_stack->type_size);
        p_stack->top_index--;
        return STACK_SUCCESS;
    }
    // printf("No data to be poped, stack is empty!\n");
    return STACK_ERROR;
}

/** ****************************************************************************
* Function : stack_top(p_stack_t p_stack, void * p_stack_data)
* @scope: Public
* @description: Writes the top value on the address pointed by p_stack_data
*               without removing it
* @return 		STACK_ERROR -> Finished execution with error
                STACK_SUCCESS -> Finished execution with success
*******************************************************************************/
int stack_top(p_stack_t p_stack, void * p_stack_data)
{
    if(stack_is_empty(p_stack) == STACK_IS_NOT_EMPTY)
    {
        void * p_data_temp;

        p_data_temp = p_stack->p_data + p_stack->top_index * p_stack->type_size;
        memcpy(p_stack_data, p_data_temp, p_stack->type_size);
        return STACK_SUCCESS;
    }
    // printf("No data to be output, stack is empty!\n");
    return STACK_ERROR;
}

/** ****************************************************************************
* Function : stack_is_full(p_stack_t p_stack)
* @scope: Public
* @description: Checks if stack is full
* @return 		STACK_IS_FULL -> Stack is full
                STACK_IS_NOT_FULL -> Stack is not full
*******************************************************************************/
int stack_is_full(p_stack_t p_stack)
{
    if(p_stack->top_index >= p_stack->num_of_elements - 1)
    {
        return STACK_IS_FULL;
    }
    return STACK_IS_NOT_FULL;
}

/** ****************************************************************************
* Function : stack_is_empty(p_stack_t p_stack)
* @scope: Public
* @description: Checks if stack is empty
* @return 		STACK_IS_EMPTY -> Stack is empty
                STACK_IS_NOT_EMPTY -> Stack is not empty
*******************************************************************************/
int stack_is_empty(p_stack_t p_stack)
{
    if(p_stack->top_index == EMPTY_STACK_INDEX)
    {
        return STACK_IS_EMPTY;
    }
    return STACK_IS_NOT_EMPTY;
}
/*************** END OF FUNCTIONS ***************************************************************************/