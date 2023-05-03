/****************************************************************************
* Title                 :   stack_public
* Filename              :   stack_public.h
* Author                :   Gabriel Tomio
* Origin Date           :   24/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/

#ifndef STACK_PUBLIC_H_
#define STACK_PUBLIC_H_

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
#define STACK_IS_NOT_EMPTY  0
#define STACK_IS_EMPTY      1

#define STACK_IS_NOT_FULL   0
#define STACK_IS_FULL       1

#define STACK_SUCCESS   0
#define STACK_ERROR     1
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct STACK *p_stack_t, **pp_stack_t;


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
/** @brief  Allocates the memory for the stack pointed by pp_stack 
 * @param   pp_stack: address of the pointer to STACK struct
 * @param   type_size: size of the type to be stored on the stack   
 * @param   num_of_elements: maximum number of elements of the stack
 * @return  STACK_ERROR -> Stack was not allocated
 *          STACK_SUCCESS -> Stack was created successfully
 */
int stack_create(pp_stack_t pp_stack, int type_size, int num_of_elements);


/** @brief   Frees the allocated memory for the stack pointed by pp_stack 
 *  @param   pp_stack: address of the pointer to STACK struct
 *  @return  STACK_ERROR -> Finished execution with error
 *           STACK_SUCCESS -> Finished execution with success 
 */
int stack_destroy(pp_stack_t pp_stack);


/** @brief  Push a new value pointed by p_stack_data to the stack pointed by p_stack 
 *  @param  p_stack: pointer to the desired stack
 *  @param  p_add_data: address to the data to be stored on top of the stack
 *  @return STACK_IS_FULL -> Finished execution with error
 *          STACK_SUCCESS -> Finished execution with success
 */
int stack_push(p_stack_t p_stack, void * p_add_data);


/** @brief  Pop the top value of the stack pointed by p_stack and write it to p_stack_data 
 *  @param  p_stack: pointer to the desired stack
 *  @param  p_read_data: address to where the stack top data will be written
 *  @return STACK_IS_EMPTY -> Finished execution with error
            STACK_SUCCESS  -> Finished execution with success
 */
int stack_pop(p_stack_t p_stack, void * p_read_data);


/** @brief  Writes the top value of the stack pointed by p_stack to p_stack_data 
 *  @param  p_read_data: address to where the stack top data will be written
 *  @note   This does not deletes the stack top data.
 *  @return STACK_IS_EMPTY -> Finished execution with error
            STACK_SUCCESS  -> Finished execution with success
 */
int stack_top(p_stack_t p_stack, void * p_read_data);

#endif
/*** End of File **************************************************************/