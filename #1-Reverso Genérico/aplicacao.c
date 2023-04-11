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
/******************************************************************************
* Includes
*******************************************************************************/
#include "aplicacao.h"

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
// TODO: UPDATE AND COPY THESE FOR EACH NON_TRIVIAL FUNCTION
/** ****************************************************************************
* Function : Dio_Init()
* @description: This function is used to initialize the Dio based on the configuration table
*  defined in dio_cfg module.  
*
* @return 		
*
*******************************************************************************/
int main(int argc, char **argv)
{
    char input_text[10];
    char * input_type;

    char line[MAXIMUM_SIZE_OF_LINE];

    char * p_new_value;

    int num_of_data = 0;

    if(fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) == NULL)
    {
        printf("Invalid Input File.");
        return FINISHED_ERROR;
    }

    input_type = strtok(line, DELIMITER_CHARACTER); // Get first information until delimiter: Ex: Tipo:int

    if(init_gen_data_storage(get_data_type(input_type)) == RGEN_ERROR)
    {
        printf("Invalid Data Type Error!\n");
        return FINISHED_ERROR;
    }

    /* fgets(A, B, C) */ 
    /* A => Where it will store the received data */ 
    /* B => Maximum Size of the Line, it will stop in this position if line has more than this size */ 
    /* C => Pointer to the file that is open by fopen or in this case, passed as a parameter */ 
    while (fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL)
    {
        int temp_int;
        char temp_char;
        void * temp_pointer;

        p_new_value = strtok(line, DELIMITER_CHARACTER);

        while ((p_new_value != NULL) && (strcmp(p_new_value, "\n") != 0))
        {
            num_of_data ++;

            if(data_type == INT_TYPE)
            {
                temp_int = atoi(p_new_value);
                temp_pointer = (void *) &temp_int;
            }
            else
            {
                temp_char = p_new_value[0];
                temp_pointer = (void *) &temp_char;
            }

            insert_gen_data(temp_pointer);

            p_new_value = strtok(NULL, DELIMITER_CHARACTER); // In this case we put NULL so it continues in the same line and on the next delimiter
        }
    }

    print_data_type();
    print_reverse_generic();

    deinit_data_storage();

    return FINISHED_SUCCESS;
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