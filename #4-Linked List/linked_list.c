/*******************************************************************************
* Title                 :   linked_list
* Filename              :   linked_list.c
* Author                :   Gabriel Tomio
* Origin Date           :   27/05/2023
* Version               :   1.0.0
* Compiler              :   GCC
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "linked_list_public.h"
#include "linked_list_private.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/** ****************************************************************************
* Function : linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp)
* @scope: Public
* @description: Initilizes the generic linked list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp)
{
    if (pp_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    *pp_linked_list = (p_linked_list_t) malloc(sizeof(linked_list_priv_t));

    if ((*pp_linked_list) == NULL)
    {
        // printf("Could not allocate memory to store linked list!\n");
        return LINKED_LIST_ERROR;
    }

    (*pp_linked_list)->current_size = 0;
    (*pp_linked_list)->type_size = type_size;
    (*pp_linked_list)->p_free_function = p_free_function_temp;
    (*pp_linked_list)->descriptor.p_first_node = NULL;
    (*pp_linked_list)->descriptor.p_last_node = NULL;
    
    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : create_node(ll_node_t ** pp_node_temp, void * p_data_temp, int type_size)
* @scope: Private
* @description: Creates a new node
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int create_node(ll_node_t ** pp_node_temp, void * p_data_temp, int type_size)
{
    *pp_node_temp = (ll_node_t*) malloc(sizeof(ll_node_t));

    if (*pp_node_temp == NULL)
    {
        // printf("Node pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    (*pp_node_temp)->p_data = (void *) malloc(type_size);

    if (*pp_node_temp == NULL)
    {
        // printf("Could not allocate memory to data!\n");
        free(*pp_node_temp);
        return LINKED_LIST_ERROR;
    }

    memcpy((*pp_node_temp)->p_data, p_data_temp, type_size);
    // printf("Alloc Pointer: %p\n", (*pp_node_temp));
    // printf("Data Pointer: %p\n", (*pp_node_temp)->p_data);
    (*pp_node_temp)->p_next_node = NULL;
    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : destroy_node(ll_node_t ** pp_node_temp, free_function_t p_free_function_temp)
* @scope: Private
* @description: Destroys the node and frees the allocated memory
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int destroy_node(ll_node_t ** pp_node_temp, free_function_t p_free_function_temp)
{
    if (*pp_node_temp == NULL)
    {
        // printf("Node pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    // printf("Memory pointer: %p\n", (*pp_node_temp));
    // printf("Data pointer: %p\n", (*pp_node_temp)->p_data);
    p_free_function_temp((*pp_node_temp)->p_data);
    free(*pp_node_temp);

    *pp_node_temp = NULL;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_destroy(pp_linked_list_t pp_linked_list)
* @scope: Public
* @description: Frees the allocated memory and allocated data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_destroy(pp_linked_list_t pp_linked_list)
{
    ll_node_t * p_node_to_destroy;
    ll_node_t * p_next_node_to_destroy;
    
    if ((*pp_linked_list == NULL) || (pp_linked_list == NULL))
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    p_node_to_destroy = (*pp_linked_list)->descriptor.p_first_node;

    for (int i = 0; i < (*pp_linked_list)->current_size; i++)
    {
        p_next_node_to_destroy = p_node_to_destroy->p_next_node;
        if(destroy_node(&p_node_to_destroy, (*pp_linked_list)->p_free_function)) 
        {
            break;
        }
        p_node_to_destroy = p_next_node_to_destroy;
    }

    free(*pp_linked_list);
    *pp_linked_list = NULL;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Insert a new element to the list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_new_node;

    if (p_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if (position_idx > p_linked_list->current_size)
    {
        // printf("Invalid insert index!\n");
        return LINKED_LIST_ERROR;
    }

    if(create_node(&p_new_node, p_linked_list_data, p_linked_list->type_size) == LINKED_LIST_ERROR)
    {
        return LINKED_LIST_ERROR;
    }

    if (p_linked_list->current_size == 0)
    {
        p_linked_list->descriptor.p_first_node = p_new_node;
        p_linked_list->descriptor.p_last_node = p_new_node;
        p_new_node->p_next_node = NULL;
    }
    else if (position_idx == 0) // Add new data to first position
    {
        p_new_node->p_next_node = p_linked_list->descriptor.p_first_node;
        p_linked_list->descriptor.p_first_node = p_new_node;
    }
    else if (p_linked_list->current_size == position_idx) // Add new data to last position
    {
        p_linked_list->descriptor.p_last_node->p_next_node = p_new_node;
        p_linked_list->descriptor.p_last_node = p_new_node;
        p_new_node->p_next_node = NULL;
    }
    else
    {
        ll_node_t * p_node_on_prev_idx;
        p_node_on_prev_idx = p_linked_list->descriptor.p_first_node;

        for (int i = 0; i < position_idx-1; i++) // Go to the index previous to the desired one
        {
            p_node_on_prev_idx = p_node_on_prev_idx->p_next_node;
        }

        p_new_node->p_next_node = p_node_on_prev_idx->p_next_node;
        p_node_on_prev_idx->p_next_node = p_new_node;
    }

    p_linked_list->current_size++;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_ordered_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Insert a new element to the list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_ordered_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, compare_function_t compare_function)
{
    ll_node_t * p_new_node;
    ll_node_t * p_node_to_compare;
    ll_node_t * p_previous_node;

    if (p_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if (position_idx > p_linked_list->current_size)
    {
        // printf("Invalid insert index!\n");
        return LINKED_LIST_ERROR;
    }

    if(create_node(&p_new_node, p_linked_list_data, p_linked_list->type_size) == LINKED_LIST_ERROR)
    {
        return LINKED_LIST_ERROR;
    }

    if (p_linked_list->current_size == 0)
    {
        p_linked_list->descriptor.p_first_node = p_new_node;
        p_linked_list->descriptor.p_last_node = p_new_node;
        p_new_node->p_next_node = NULL;
    }
    else
    {
        p_node_to_compare = p_linked_list->descriptor.p_first_node;
        p_previous_node = NULL;
        while ((compare_function(p_new_node->p_data, p_node_to_compare->p_data) == 0) || (p_node_to_compare == NULL))
        {
            p_previous_node = p_node_to_compare;
            p_node_to_compare = p_node_to_compare->p_next_node;
        }

        if (p_node_to_compare == p_linked_list->descriptor.p_first_node) // Add new data to first position
        {
            p_new_node->p_next_node = p_linked_list->descriptor.p_first_node;
            p_linked_list->descriptor.p_first_node = p_new_node;
        }
        else if (p_node_to_compare == NULL) // Add new data to last position
        {
            p_linked_list->descriptor.p_last_node->p_next_node = p_new_node;
            p_linked_list->descriptor.p_last_node = p_new_node;
            p_new_node->p_next_node = NULL;
        }
        else
        {
            p_new_node->p_next_node = p_previous_node->p_next_node;
            p_previous_node->p_next_node = p_new_node;
        }
    }
    
    p_linked_list->current_size++;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Destroy the node on the selected index and returns it on p_linked_list_data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_node_to_destroy;

    if (p_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if (p_linked_list->current_size == 0)
    {
        // printf("The linked list is empty!\n");
        return LINKED_LIST_ERROR;
    }
    
    if (p_linked_list->current_size == 1)
    {
        p_node_to_destroy = p_linked_list->descriptor.p_first_node;
        p_linked_list->descriptor.p_first_node = NULL;
        p_linked_list->descriptor.p_last_node = NULL;
    }
    else if (position_idx == 0) // Remove from first position
    {
        p_node_to_destroy = p_linked_list->descriptor.p_first_node;
        p_linked_list->descriptor.p_first_node = p_linked_list->descriptor.p_first_node->p_next_node;
    }
    else if (position_idx == p_linked_list->current_size - 1) // Remove from last position
    {
        ll_node_t * p_node_on_prev_idx;
        p_node_on_prev_idx = p_linked_list->descriptor.p_first_node;

        for (int i = 0; i < position_idx-1; i++) // Go to the index previous to the desired one
        {
            p_node_on_prev_idx = p_node_on_prev_idx->p_next_node;
        }
        p_node_to_destroy = p_node_on_prev_idx->p_next_node;
        p_node_on_prev_idx->p_next_node = NULL;
        p_linked_list->descriptor.p_last_node = p_node_on_prev_idx;
    }
    else
    {
        ll_node_t * p_node_on_prev_idx;
        p_node_on_prev_idx = p_linked_list->descriptor.p_first_node;

        for (int i = 0; i < position_idx-1; i++) // Go to the index previous to the desired one
        {
            p_node_on_prev_idx = p_node_on_prev_idx->p_next_node;
        }
        p_node_to_destroy = p_node_on_prev_idx->p_next_node;
        p_node_on_prev_idx->p_next_node = p_node_on_prev_idx->p_next_node->p_next_node;

    }

    memcpy(p_linked_list_data, p_node_to_destroy->p_data, p_linked_list->type_size);
    destroy_node(&p_node_to_destroy, p_linked_list->p_free_function);
    
    p_linked_list->current_size--;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Returns the data on the node and write on p_linked_list_data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_node_to_output;

    if (p_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if ((p_linked_list->current_size == 0) || (position_idx > p_linked_list->current_size-1))
    {
        // printf("Invalid position index!\n");
        return LINKED_LIST_ERROR;
    }
    
    p_node_to_output = p_linked_list->descriptor.p_first_node;

    for (int i = 0; i < position_idx; i++)
    {
        p_node_to_output = p_node_to_output->p_next_node;
    }

    memcpy(p_linked_list_data, p_node_to_output->p_data, p_linked_list->type_size);

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx)
* @scope: Public
* @description: Prints the selected node data with the given function
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx)
{
    ll_node_t * p_node_to_print;

    if (p_linked_list == NULL)
    {
        // printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if ((p_linked_list->current_size == 0) || (position_idx > p_linked_list->current_size-1))
    {
        // printf("Invalid position index!\n");
        return LINKED_LIST_ERROR;
    }

    p_node_to_print = p_linked_list->descriptor.p_first_node;

    for (int i = 0; i < position_idx; i++)
    {
        p_node_to_print = p_node_to_print->p_next_node;
    }

    p_print_function(p_node_to_print->p_data);
    
    return LINKED_LIST_SUCCESS;
}
/*************** END OF FUNCTIONS ***************************************************************************/