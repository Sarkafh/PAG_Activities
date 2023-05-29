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
#define MINIMUM_SIZE_QUEUE      2

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/

	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct LINKED_LIST
{
    ll_descriptor_t descriptor;
    free_function_t p_free_function;
    int type_size;
    int current_size;
} linked_list_priv_t;


typedef structs
{
    void * p_data;
    ll_node_t * p_next_node;
} ll_node_t;

typedef struct
{
    ll_node_t * p_first_node;
    ll_node_t * p_last_node;
} ll_descriptor_t;



/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
int create_node(ll_node_t * p_node_temp, void * p_data_temp, int type_size);
int destroy_node(ll_node_t * p_node_temp, free_function_t p_free_function_temp);


#endif
/*** End of File **************************************************************/