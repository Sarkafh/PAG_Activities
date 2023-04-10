/*******************************************************************************
* Title                 :   aplicacao  
* Filename              :   aplicacao.c
* Author                :   Gabriel Tomio
* Origin Date           :   01/04/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   Reverse generic input
*
*******************************************************************************/
/** @file aplicacao.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "rgen_publico.h"
#include "rgen_privado.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void print_reverse_generic(void * p_data, var_type_t data_type, int num_of_data)
{   
    print_data_type(data_type);

    for(int i = (num_of_data - 1); i >= 0; i--)
    {
        if(data_type == INT_TYPE)
        {
            int number = ((int*)p_data)[i];
            int remainder;
            printf("(");
            while (number != 0) 
            {   
                remainder = number % 10;
                number /= 10;
                printf("%d", remainder);
            }
            printf(");\n");
        }
        else
        {
            printf("(%c);\n",((char*)p_data)[i]);
        }
    }
}

void print_data_type(var_type_t data_type)
{
    printf("Tipo_do_dado:");
    if(data_type == INT_TYPE)
    {
        printf("int;\n");
    }
    else if(data_type == CHAR_TYPE)
    {
        printf("char;\n");
    }
    else
    {
        printf("none;\n");
    }
}

int get_type_size(var_type_t var_type)
{
    switch (var_type)
    {
        case INT_TYPE:
            return (sizeof(int));
        break;

        case CHAR_TYPE:
            return (sizeof(char));
        break;
        
        default:
            printf("get_type_size() -> Invalid Type\n");
            return -1;
        break;
    }
}

var_type_t get_data_type(char var_type_text[])
{
    if(strcmp(var_type_text, "Tipo:int") == 0)
    {
        return INT_TYPE;
    }
    else if (strcmp(var_type_text, "Tipo:char") == 0)
    {
        return CHAR_TYPE;
    }

    printf("get_data_type() -> Invalid Type\n");
    return ERROR_TYPE;
}
/*************** END OF FUNCTIONS ***************************************************************************/