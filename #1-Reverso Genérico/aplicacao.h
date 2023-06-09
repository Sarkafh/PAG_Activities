/****************************************************************************
* Title                 :   aplicacao
* Filename              :   aplicacao.h
* Author                :   Gabriel Tomio
* Origin Date           :   01/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   None
*****************************************************************************/
#ifndef APLICACAO_H_
#define APLICACAO_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rgen_publico.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define MAXIMUM_SIZE_OF_LINE    1000
#define DELIMITER_CHARACTER     ";"
#define FINISHED_ERROR          1
#define FINISHED_SUCCESS        0

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/

	
/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
var_type_t get_data_type(char var_type_text[]);


#endif
/*** End of File **************************************************************/