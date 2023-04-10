/****************************************************************************
* Title                 :   rgen_publico
* Filename              :   rgen_publico.h
* Author                :   Gabriel Tomio
* Origin Date           :   01/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/
/** @file aplicacao.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
#ifndef RGEN_PUBLICO_H_
#define RGEN_PUBLICO_H_

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

	
/******************************************************************************
* Typedefs
*******************************************************************************/
typedef enum {ERROR_TYPE, INT_TYPE, CHAR_TYPE} var_type_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void print_reverse_generic(void * p_data, var_type_t data_type, int num_of_data);
var_type_t get_data_type(char var_type_text[]);
int get_type_size(var_type_t var_type);


#endif
/*** End of File **************************************************************/