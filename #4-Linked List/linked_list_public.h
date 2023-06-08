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
* Example:
*******************************************************************************/
// void print_int(void * p_data)
// {
//     int * value = (int *) p_data;
//     printf("Init Dado: %d\n", *value);
// }

// void print_int2(void * p_data)
// {
//     int * value = (int *) p_data;
//     printf("After Dado: %d\n", *value);
// }

// void free_int(void * p_data)
// {
//     int * value = (int *) p_data;
//     free(value);
// }

// int main(int argc, char **argv)
// {
//     p_linked_list_t my_linked_list;
//     int value = 1;

//     linked_list_create(&my_linked_list, sizeof(int), free_int); // Create Linked List

//     for (int i = 0; i < 10; i++)
//     {
//         linked_list_insert(my_linked_list, &value, i); // Insert elements on the linked list on the given index
//         value++;
//     }
//     value = 50;
//     linked_list_insert(my_linked_list, &value, 1); // Insert elements on the linked list on the given index

//     for (int i = 0; i < 11; i++)
//     {
//         linked_list_print(my_linked_list, print_int, i); // Prints the elements on the linked list on the given index
//     }

//     for (int i = 5; i > 0; i--)
//     {
//         linked_list_remove(my_linked_list, &value, i*2); // Remove the elements on the linked list on the given index
//     }

//     for (int i = 0; i < 11-5; i++)
//     {
//         linked_list_print(my_linked_list, print_int2, i); // Prints the elements on the linked list on the given index
//     }

//     linked_list_destroy(&my_linked_list); // Destroys all of the elements and data on the linked list and destroys itself
//     return FINISHED_SUCCESS;
// }

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
typedef int (*compare_function_t)(void*, void*);
/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/

/** ****************************************************************************
* Function : linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp)
* @scope: Public
* @description: Initilizes the generic linked list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_create(pp_linked_list_t pp_linked_list, int type_size, free_function_t p_free_function_temp);


/** ****************************************************************************
* Function : linked_list_destroy(pp_linked_list_t pp_linked_list)
* @scope: Public
* @description: Frees the allocated memory and allocated data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_destroy(pp_linked_list_t pp_linked_list);


/** ****************************************************************************
* Function : linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Insert a new element to the list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);

/** ****************************************************************************
* Function : linked_list_ordered_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, compare_function_t compare_function)
* @scope: Public
* @description: Insert a new element to the list
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_ordered_insert(p_linked_list_t p_linked_list, void * p_linked_list_data, compare_function_t compare_function);
// todo: document this

/** ****************************************************************************
* Function : linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Destroy the node on the selected index and returns it on p_linked_list_data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_remove(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);


/** ****************************************************************************
* Function : linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx)
* @scope: Public
* @description: Returns the data on the node and write on p_linked_list_data
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_get(p_linked_list_t p_linked_list, void * p_linked_list_data, int position_idx);


/** ****************************************************************************
* Function : linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx)
* @scope: Public
* @description: Prints the selected node data with the given function
* @return 		LINKED_LIST_ERROR -> Finished execution with error
                LINKED_LIST_SUCCESS -> Finished execution with success
*******************************************************************************/
int linked_list_print(p_linked_list_t p_linked_list, print_function_t p_print_function, int position_idx);

#endif
/*** End of File **************************************************************/