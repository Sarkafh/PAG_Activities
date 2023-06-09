/****************************************************************************
* Title                 :   linked_list_private
* Filename              :   linked_list_private.h
* Author                :   Gabriel Tomio
* Origin Date           :   27/05/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/

#ifndef LINKED_LIST_PRIVATE_H_
#define LINKED_LIST_PRIVATE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/

	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct ll_node_t ll_node_t;

struct ll_node_t
{
    void* p_data;
    ll_node_t* p_next_node;
};

typedef struct
{
    ll_node_t * p_first_node;
    ll_node_t * p_last_node;
} ll_descriptor_t;

typedef struct LINKED_LIST
{
    ll_descriptor_t descriptor;
    free_function_t p_free_function;
    int type_size;
    int current_size;
} linked_list_priv_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/

/** ****************************************************************************
* Function : create_node(ll_node_t ** pp_node_temp, void * p_data_temp, int type_size)
* @scope: Private
* @description: Creates a new node
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int create_node(ll_node_t ** pp_node_temp, void * p_data_temp, int type_size);

/** ****************************************************************************
* Function : destroy_node(ll_node_t ** pp_node_temp, free_function_t p_free_function_temp)
* @scope: Private
* @description: Destroys the node and frees the allocated memory
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int destroy_node(ll_node_t ** pp_node_temp, free_function_t p_free_function_temp);


#endif
/*** End of File **************************************************************/