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
* Function : queue_create(pp_queue_t pp_queue, int type_size, int num_of_elements)
* @scope: Public
* @description: Initilizes the generic queue
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp)
{
    if (pp_linked_list == NULL)
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    *pp_linked_list = (p_linked_list_t) malloc(sizeof(linked_list_priv_t));

    if ((*pp_linked_list) == NULL)
    {
        printf("Could not allocate memory to store linked list!\n");
        return LINKED_LIST_ERROR;
    }

    (*pp_linked_list)->current_size = 0;
    (*pp_linked_list)->type_size = type_size;
    (*pp_linked_list)->p_free_function = p_free_function_temp;
    (*pp_linked_list)->descriptor.p_first_node = NULL;
    (*pp_linked_list)->descriptor.p_last_node = NULL;
    
    return LINKED_LIST_SUCCESS;
}

// todo: document this
int create_node(ll_node_t * p_node_temp, void * p_data_temp, int type_size)
{
    *p_node_temp = (ll_node_t) malloc(sizeof(ll_node_t));

    if (*p_node_temp == NULL)
    {
        printf("Node pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    *p_node_temp->p_data = (void *) malloc(type_size);

    if (*p_node_temp == NULL)
    {
        printf("Could not allocate memory to data!\n");
        free(*p_node_temp);
        return LINKED_LIST_ERROR;
    }

    memcpy(*p_node_temp->p_data, p_data_temp, type_size);

    *p_node_temp->p_next_node = NULL;
    return LINKED_LIST_SUCCESS;
}

// todo: document this
int destroy_node(ll_node_t * p_node_temp, free_function_t p_free_function_temp)
{
    if (*p_node_temp == NULL)
    {
        printf("Node pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    p_free_function_temp(p_node_temp->p_data);
    free(p_node_temp);

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : linked_list_destroy(pp_linked_list_t pp_linked_list)
* @scope: Public
* @description: Frees the allocated memory
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_destroy(pp_linked_list_t pp_linked_list)
{
    if ((*pp_linked_list == NULL) || (pp_linked_list == NULL))
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    ll_node_t * p_node_to_destroy;
    p_node_to_destroy = (*pp_linked_list)->descriptor.p_first_node;

    for (int i = 0; i < (*pp_linked_list)->current_size; i++)
    {
        if(destroy_node(p_node_to_destroy, (*pp_linked_list)->p_free_function)) 
        {
            break;
        }
        p_node_to_destroy = p_node_to_destroy->p_next_node;
    }

    free(*pp_linked_list);
    *pp_linked_list = NULL;

    return LINKED_LIST_SUCCESS;
}

/** ****************************************************************************
* Function : queue_enqueue(p_queue_t p_queue, void * p_queue_data)
* @scope: Public
* @description: Add a new element in the queue
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_new_node;

    if (p_linked_list == NULL)
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if (position_idx > p_linked_list->current_size)
    {
        printf("Invalid insert index!\n");
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

        for (int i = 0; i < position_idx; i++) // Go to the index previous to the desired one
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
* Function : queue_dequeue(p_queue_t p_queue, void * p_queue_data)
* @scope: Public
* @description: Deletes the queue top element
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_node_to_destroy;

    if (p_linked_list == NULL)
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if (p_linked_list->current_size == 0)
    {
        printf("The linked list is empty!\n");
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
    destroy_node(p_node_to_destroy, p_linked_list->p_free_function);
    
    p_linked_list->current_size--;

    return LINKED_LIST_SUCCESS;
}

int linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
{
    ll_node_t * p_node_to_output;

    if (p_linked_list == NULL)
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if ((p_linked_list->current_size == 0) || (position_idx > p_linked_list->current_size-1))
    {
        printf("Invalid position index!\n");
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

int linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx)
{
    ll_node_t * p_node_to_print;

    if (p_linked_list == NULL)
    {
        printf("Linked list pointer is invalid!\n");
        return LINKED_LIST_ERROR;
    }

    if ((p_linked_list->current_size == 0) || (position_idx > p_linked_list->current_size-1))
    {
        printf("Invalid position index!\n");
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