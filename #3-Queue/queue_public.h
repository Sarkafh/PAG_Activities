/****************************************************************************
* Title                 :   queue_public
* Filename              :   queue_public.h
* Author                :   Gabriel Tomio
* Origin Date           :   24/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/

#ifndef QUEUE_PUBLIC_H_
#define QUEUE_PUBLIC_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define UNLIMITED_SIZE_QUEUE    0

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/
#define QUEUE_IS_NOT_EMPTY  0
#define QUEUE_IS_EMPTY      1

#define QUEUE_IS_NOT_FULL   0
#define QUEUE_IS_FULL       1

#define QUEUE_SUCCESS   0
#define QUEUE_ERROR     1
	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct QUEUE *p_queue_t, **pp_queue_t;


/******************************************************************************
* EXAMPLE:
* p_queue_t my_queue;
* mytype_t my_type = 1;
* queue_create(&my_queue, sizeof(mytype_t), 10); // allocates a queue of type mytype_t with size 10
* queue_enqueue(my_queue, (void *) &my_type);
* my_type = 10;
* queue_enqueue(my_queue, (void *) &my_type);
* queue_dequeue(my_queue, (void *) &my_type);
* printf("value: %d", mytype); // prints (1)
* queue_dequeue(my_queue, (void *) &my_type);
* printf("value: %d", mytype); // prints (10)
* queue_destroy(&my_queue); // frees the memory allocated for storage
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
/** @brief  Allocates the memory for the queue pointed by pp_queue 
 * @param   pp_queue: address of the pointer to QUEUE struct
 * @param   type_size: size of the type to be stored on the queue   
 * @param   num_of_elements: maximum number of elements of the queue
 * @return  QUEUE_ERROR -> Stack was not allocated
 *          QUEUE_SUCCESS -> Stack was created successfully
 */
int queue_create(pp_queue_t pp_queue, int type_size, int num_of_elements);


/** @brief   Frees the allocated memory for the queue pointed by pp_queue 
 *  @param   pp_queue: address of the pointer to QUEUE struct
 *  @return  QUEUE_ERROR -> Finished execution with error
 *           QUEUE_SUCCESS -> Finished execution with success 
 */
int queue_destroy(pp_queue_t pp_queue);


/** @brief  Push a new value pointed by p_queue_data to the queue pointed by p_queue 
 *  @param  p_queue: pointer to the desired queue
 *  @param  p_add_data: address to the data to be stored on front of the queue
 *  @return QUEUE_IS_FULL / QUEUE_ERROR -> Finished execution with error
 *          QUEUE_SUCCESS -> Finished execution with success
 */
int queue_enqueue(p_queue_t p_queue, void * p_add_data);


/** @brief  Dequeues the front value of the queue pointed by p_queue and write it to p_queue_data 
 *  @param  p_queue: pointer to the desired queue
 *  @param  p_read_data: address to where the queue front data will be written
 *  @return QUEUE_IS_EMPTY / QUEUE_ERROR -> Finished execution with error
            QUEUE_SUCCESS  -> Finished execution with success
 */
int queue_dequeue(p_queue_t p_queue, void * p_read_data);


/** @brief  Writes the front value of the queue pointed by p_queue to p_read_data 
 *  @param  p_queue: pointer to the desired queue
 *  @param  p_read_data: address to where the queue front data will be written
 *  @note   This does not deletes the queue front data.
 *  @return QUEUE_IS_EMPTY / QUEUE_ERROR -> Finished execution with error
            QUEUE_SUCCESS  -> Finished execution with success
 */
int queue_front(p_queue_t p_queue, void * p_read_data);


/** @brief  Writes the current size of the queue pointed by p_queue to current_size 
 *  @param  p_queue: pointer to the desired queue
 *  @param  current_size: address to where the current size will be written
 *  @return QUEUE_ERROR -> Finished execution with error
            QUEUE_SUCCESS  -> Finished execution with success
 */
int queue_current_size(p_queue_t p_queue, int * current_size);


/** @brief  Writes the allocated number of elemets of the queue pointed by p_queue to capacity 
 *  @param  p_queue: pointer to the desired queue
 *  @param  capacity: address to where the current capacity will be written
 *  @return QUEUE_ERROR -> Finished execution with error
            QUEUE_SUCCESS  -> Finished execution with success
 */
int queue_capacity(p_queue_t p_queue, int * capacity);


#endif
/*** End of File **************************************************************/