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
void * store_data(void * p_memory, void * p_data, int data_size);

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
    void * p_stored_data;

    var_type_t data_type;
    int data_type_size;
    
    int num_of_data = 0;

    p_stored_data = malloc(MAX_FULL_DATA_SIZE_BYTES);

    if(fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) == NULL)
    {
        printf("Invalid Input File.");
        return FINISHED_ERROR;
    }

    input_type = strtok(line, DELIMITER_CHARACTER);
    
    data_type = get_data_type(input_type);
    data_type_size = get_type_size(data_type);

    if(data_type_size == -1)
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

            p_stored_data = store_data(p_stored_data, temp_pointer, data_type_size);

            p_new_value = strtok(NULL, DELIMITER_CHARACTER); // In this case we put NULL so it continues in the same line and on the next delimiter
        }
    }

    p_stored_data = p_stored_data - num_of_data*data_type_size; // Restore pointer to its initial value

    print_reverse_generic(p_stored_data, data_type, num_of_data);

    free(p_stored_data);

    return FINISHED_SUCCESS;
}

void * store_data(void * p_memory, void * p_data, int data_size)
{
    for(int i = 0; i < data_size; i++)
    {
        ((char *)p_memory)[i] = ((char *)p_data)[i];
    }
    return (void *)p_memory + data_size;
}
/*************** END OF FUNCTIONS ***************************************************************************/