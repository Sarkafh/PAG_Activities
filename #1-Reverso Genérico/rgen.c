/*******************************************************************************
* Title                 :   rgen  
* Filename              :   rgen.c
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
#include "rgen_publico.h"
#include "rgen_privado.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/

/** ****************************************************************************
* Function : init_gen_data_storage(var_type_t data_type)
* @scope: Public
* @description: Initilizes the generic type info struct
* @return 		RGEN_ERROR -> cannot initialize current data type
                RGEN_SUCCESS -> data was successfuly initialized
*******************************************************************************/
int init_gen_data_storage(var_type_t data_type)
{
    generic_data_info.data_type = data_type;
    generic_data_info.data_size = get_type_size(data_type);

    if(generic_data_info.data_size == -1)
    {
        return RGEN_ERROR;
    }

    generic_data_info.data_count = 0;
    generic_data_info.p_start_address = malloc(MAX_ALOCATED_SIZE*generic_data_info.data_size);
    generic_data_info.p_last_address = generic_data_info.p_start_address;

    return RGEN_SUCCESS;
}

/** ****************************************************************************
* Function : insert_gen_data(void * p_data)
* @scope: Public
* @description: Insert a new data onto the allocated memory
*******************************************************************************/
void insert_gen_data(void * p_data)
{
    generic_data_info.data_count++;
    generic_data_info.p_last_address = store_data(generic_data_info.p_last_address, p_data, generic_data_info.data_size);
}

/** ****************************************************************************
* Function : deinit_data_storage(void)
* @scope: Public
* @description: Frees the allocated memory
*******************************************************************************/
void deinit_data_storage(void)
{
    free(generic_data_info.p_start_address);
}

/** ****************************************************************************
* Function : init_gen_data_storage(var_type_t data_type)
* @scope: Public
* @description: gets the current stored data type
* @return 		generic_data_info.data_type
*******************************************************************************/
var_type_t get_gen_type(void)
{
    return(generic_data_info.data_type);
}

/** ****************************************************************************
* Function : store_data(void * p_memory, void * p_data, int data_size)
* @scope: Private
* @description: gets the current stored data type
* @return 		void pointer to the next free address
*******************************************************************************/
void * store_data(void * p_memory, void * p_data, int data_size)
{
    for(int i = 0; i < data_size; i++)
    {
        ((char *)p_memory)[i] = ((char *)p_data)[i];
    }
    return (void *)p_memory + data_size;
}

/** ****************************************************************************
* Function : print_reverse_generic(void)
* @scope: Public
* @description: prints the reverse of the stored data
*******************************************************************************/
void print_reverse_generic(void)
{   
    for(int i = (generic_data_info.data_count - 1); i >= 0; i--)
    {
        if(generic_data_info.data_type == INT_TYPE)
        {
            int number = ((int*)generic_data_info.p_start_address)[i];
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
            printf("(%c);\n",((char*)generic_data_info.p_start_address)[i]);
        }
    }
}

/** ****************************************************************************
* Function : print_data_type(void)
* @scope: Public
* @description: prints the current data type
*******************************************************************************/
void print_data_type(void)
{
    printf("Tipo_do_dado:");
    if(generic_data_info.data_type == INT_TYPE)
    {
        printf("int;\n");
    }
    else if(generic_data_info.data_type == CHAR_TYPE)
    {
        printf("char;\n");
    }
    else
    {
        printf("none;\n");
    }
}

/** ****************************************************************************
* Function : get_type_size(var_type_t var_type)
* @scope: Private
* @description: prints the current data type
* @return       byte size of the current type
                error -> returns (-1)
*******************************************************************************/
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
/*************** END OF FUNCTIONS ***************************************************************************/