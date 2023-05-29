/****************************************************************************
* Title                 :   linked_list_public
* Filename              :   linked_list_public.h
* Author                :   Gabriel Tomio
* Origin Date           :   27/05/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/

#ifndef LINKED_LIST_PUBLIC_H_
#define LINKED_LIST_PUBLIC_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/
#define LINKED_LIST_SUCCESS   0
#define LINKED_LIST_ERROR     1
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct LINKED_LIST *p_linked_list_t, **pp_linked_list_t;
typedef void (*free_function_t)(void*);
typedef void (*print_function_t)(void*);
/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
int linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp);
int linked_list_destroy(pp_linked_list_t pp_linked_list);
int linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);
int linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);
int linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);
int linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx);

#endif
/*** End of File **************************************************************/