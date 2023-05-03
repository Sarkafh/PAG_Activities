/*******************************************************************************
* Title                 :   aplicacao  
* Filename              :   aplicacao.c
* Author                :   Gabriel Tomio
* Origin Date           :   01/05/2023
* Version               :   1.0.0
* Compiler              :   GCC
* Notes                 :   Game of Towers
*
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "aplicacao.h"

/******************************************************************************
* Function Definitions
*******************************************************************************/


/** ****************************************************************************
* Function : main(int argc, char **argv)
* @description: gets the towers from an input file and reorders them
* @return 		FINISHED_ERROR -> finished operation with error
                FINISHED_SUCCESS -> finished operation successfully
*******************************************************************************/
int main(int argc, char **argv)
{
    colored_stack_t * p_colored_stack[MAX_NUMBER_OF_STACKS];
    int stack_size[MAX_NUMBER_OF_STACKS];
    char line[MAXIMUM_SIZE_OF_LINE];
    int line_counter = 0;
    int temp_stack_size = 0;
    int colored_stack_idx = 0;
    int num_of_stacks = 0;

    while((fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL))
    {
        line_counter++;
        if ((line_counter != 1)&&(line_counter != 2)&&(strcmp(line, "\n") != 0))
        {
            /* Find stack color */
            colored_stack_idx++;
            char stack_color_text[SIZE_OF_STACK_TOKEN + SIZE_OF_COLOR_TEXT];

            for (int i = 0; i < SIZE_OF_STACK_TOKEN + SIZE_OF_COLOR_TEXT; i++)
            {
                stack_color_text[i] = line[i];
            }
            p_colored_stack[colored_stack_idx] = (colored_stack_t*)malloc(sizeof(colored_stack_t));
            *p_colored_stack[colored_stack_idx] = text2coloredstack(stack_color_text);

            int piece_start_index = 0;
            int piece_stop_index = 0;

            for (int i = 0; i < strlen(line); i++)
            {
                if(line[i] == '[')
                {
                    piece_start_index = i;
                }
                else if (line[i] == ']')
                {
                    piece_stop_index = i;
                    break;
                }
            }

            if(piece_start_index != piece_stop_index-1) // check if the list is empty
            {
                int size_of_current_stack = 1; // It starts in one to count the last piece
                for (int i = piece_start_index + 1; i < piece_stop_index; i++)
                {
                    if(line[i] == ';')
                    {
                        size_of_current_stack++;
                    }
                }

                stack_size[colored_stack_idx] = size_of_current_stack;
                stack_create(&(p_colored_stack[colored_stack_idx]->stack_id), sizeof(piece_t), stack_size[colored_stack_idx]);
                temp_stack_size += size_of_current_stack;

                char piece_info_text[SIZE_OF_PIECE_TOKEN + SIZE_OF_COLOR_TEXT+1];
                int piece_info_idx = 0;
                piece_t current_piece;
                for (int i = piece_start_index + 1; i < piece_stop_index; i++)
                {
                    if(line[i] == ';')
                    {
                        current_piece = text2piece(piece_info_text);
                        stack_push(p_colored_stack[colored_stack_idx]->stack_id, (void *)&current_piece);
                        piece_info_idx = 0;
                    }
                    else if (i == piece_stop_index-1)
                    {
                        piece_info_text[piece_info_idx] = line[i];
                        current_piece = text2piece(piece_info_text);
                        stack_push(p_colored_stack[colored_stack_idx]->stack_id, (void *)&current_piece);
                        piece_info_idx = 0;
                    }
                    else
                    {
                        piece_info_text[piece_info_idx] = line[i];
                        piece_info_idx++;
                    }
                }
            }
        }
    }

    p_colored_stack[TEMP_STACK_IDX] = (colored_stack_t*)malloc(sizeof(colored_stack_t));
    stack_size[TEMP_STACK_IDX] = temp_stack_size;
    p_colored_stack[TEMP_STACK_IDX]->color = NO_COLOR;
    stack_create(&(p_colored_stack[TEMP_STACK_IDX]->stack_id), sizeof(piece_t), stack_size[TEMP_STACK_IDX]);

    num_of_stacks = colored_stack_idx;
    
    /* Algorithm initialization */
    int expected_piece_size[MAX_NUMBER_OF_STACKS];
    expected_piece_size[TEMP_STACK_IDX] = 0;

    for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
    {
        expected_piece_size[stack_idx] = stack_size[stack_idx];
    }
    
    /* Algorithm Start */
    int b_stack_temp_finished = 0;
    piece_t current_piece;
    int empty_stack_count = 0;
    int no_possible_moves_counter = 0;
    int b_no_possible_moves_flag  = 0;

    /* Store pieces on the temporary stack */
    while ((b_stack_temp_finished == 0)&&(b_no_possible_moves_flag == 0))
    {
        for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
        {
            if(stack_top(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece) != STACK_ERROR)
            {
                empty_stack_count = 0;
                for (int stack_idx_2 = 1; stack_idx_2 <= num_of_stacks; stack_idx_2++)
                {
                    if (current_piece.color == p_colored_stack[stack_idx_2]->color) /* find index to current piece color */
                    {
                        if(current_piece.size == expected_piece_size[stack_idx_2])
                        {
                            no_possible_moves_counter = 0;
                            expected_piece_size[stack_idx_2]--;
                            stack_pop(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece);
                            stack_push(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece);
                            break;
                        }
                        else
                        {
                            if(no_possible_moves_counter++ >= MAX_IMPOSSIBLE_MOVES)
                            {
                                b_no_possible_moves_flag = 1;
                            }
                        }
                    }
                }
            }
            else
            {
                if(++empty_stack_count >= (num_of_stacks))
                {
                    b_stack_temp_finished = 1;
                    break;
                }
            }
        }
    }

    /* Unstack the pieces stored on the temporary stack onto their correct stack colors */
    if (b_no_possible_moves_flag != 1)
    {
        for(int piece_idx = 0; piece_idx < stack_size[TEMP_STACK_IDX]; piece_idx++)
        {
            if(stack_pop(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece) != STACK_ERROR)
            {
                for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
                {
                    if(current_piece.color == p_colored_stack[stack_idx]->color) /* find index to current piece color */
                    {
                        stack_push(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    /* Algorithm End */

    /* Print Output stacks */
    if (b_no_possible_moves_flag == 1)
    {
        char * print_text;
        print_text = (char *)malloc(10*sizeof(char));
        printf("Pt=[];\n");
        for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
        {
            coloredstack2text(*p_colored_stack[stack_idx], print_text);
            printf("%s=[];\n", print_text);
        }
        free(print_text);
    }
    else
    {
        printf("Pt=[];\n");
        char * print_text;
        print_text = (char *)malloc(10*sizeof(char));
        // for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
        for (int color_idx = 1; color_idx <= NUM_OF_COLORS; color_idx++)
        {
            for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
            {
                if(color_idx == p_colored_stack[stack_idx]->color)
                {
                    coloredstack2text(*p_colored_stack[stack_idx], print_text);
                    printf("%s=[",print_text);

                    /* Stack onto the temp stack to revert the print order */
                    for (int piece_idx = 0; piece_idx < stack_size[stack_idx]; piece_idx++)
                    {
                        stack_pop(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece);
                        stack_push(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece);
                    }

                    for (int piece_idx = 0; piece_idx < stack_size[stack_idx]; piece_idx++)
                    {
                        stack_pop(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece);
                        piece2text(current_piece, print_text);
                        if (piece_idx == stack_size[stack_idx] - 1)
                        {
                            printf("%s", print_text);
                        }
                        else
                        {
                            printf("%s;", print_text);
                        } 
                    }
                    printf("];\n");
                }
            }
        }
        free(print_text);
    }
    
   
    for (int stack_idx = 0; stack_idx <= num_of_stacks; stack_idx++)
    {
        stack_destroy(&(*p_colored_stack[stack_idx]).stack_id);
        free(p_colored_stack[stack_idx]);
    }

    return FINISHED_SUCCESS;
}


/** ****************************************************************************
* Function : text2coloredstack()
* @description: Converts the input text into a colored_stack_t type
* @note:        Here the input_text must be similar to "PCaz"
* @return 		colored_stack_t object
*******************************************************************************/
colored_stack_t text2coloredstack(char input_text[])
{
    char temp_stack_color[] = AZUL_TEXT;
    colored_stack_t temp_colored_stack = (colored_stack_t){(p_stack_t)0, NO_COLOR};
    color_t temp_color;

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_stack_color[i] = input_text[i + strlen(STACK_TOKEN)];
    }

    temp_color = text2color(temp_stack_color);
    temp_colored_stack.color = temp_color;

    return temp_colored_stack;
}


/** ****************************************************************************
* Function : coloredstack2text()
* @description: Converts the input text into a colored_stack_t type
* @note:        Here the input_text must be similar to "PCaz"
* @return 		colored_stack_t object
*******************************************************************************/
void coloredstack2text(colored_stack_t colored_stack_temp, char * temp_text)
{
    char color_text[SIZE_OF_COLOR_TEXT +1];
    for (int i = 0; i < SIZE_OF_STACK_TOKEN; i++)
    {
        temp_text[i] = STACK_TOKEN[i];
    }

    color2text(colored_stack_temp.color, color_text);

    for (int i = 0; i < strlen(color_text); i++)
    {
        temp_text[i+SIZE_OF_STACK_TOKEN] = color_text[i];
    }
}


/** ****************************************************************************
* Function : text2piece()
* @description: Converts the input text into a piece_t type
* @note:        Here the input_text must be similar to "paz1"
* @return 		piece_t object
*******************************************************************************/
piece_t text2piece(char input_text[])
{
    piece_t temp_piece;
    char temp_piece_color[] = AZUL_TEXT;
    char temp_piece_size[strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_PIECE_TOKEN];
    int piece_size_size = strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_PIECE_TOKEN;

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_piece_color[i] = input_text[i + strlen(PIECE_TOKEN)];
    }
    temp_piece.color = text2color(temp_piece_color);

    for (int i = 0; i < piece_size_size; i++)
    {
        temp_piece_size[i] = input_text[SIZE_OF_COLOR_TEXT + SIZE_OF_PIECE_TOKEN + i];
    }
    temp_piece.size = atoi(temp_piece_size);
    
    return temp_piece;
}


/** ****************************************************************************
* Function : piece2text()
* @description: Converts the input text into a piece_t type
* @note:        Here the input_text must be similar to "paz1"
* @return 		piece_t object
*******************************************************************************/
void piece2text(piece_t piece_temp, char * temp_text)
{
    char color_text[SIZE_OF_COLOR_TEXT +1];
    char piece_size_text[10];
    int text_offset=0;

    for (int i = 0; i < SIZE_OF_PIECE_TOKEN; i++)
    {
        temp_text[i] = PIECE_TOKEN[i];
    }

    text_offset = SIZE_OF_PIECE_TOKEN;
    color2text(piece_temp.color, color_text);

    for (int i = 0; i < strlen(color_text); i++)
    {
        temp_text[i+text_offset] = color_text[i];
    }

    text_offset += strlen(color_text);
    sprintf(piece_size_text, "%d", piece_temp.size);
    // itoa(piece_temp.size, piece_size_text, 10);
    for (int i = 0; i < strlen(piece_size_text); i++)
    {
        temp_text[i+text_offset] = piece_size_text[i];
    }
}

/** ****************************************************************************
* Function : text2color()
* @description: Converts the input text into a color_t type
* @note:        Here the input_text must be similar to "az"
* @return 		color_t object
*******************************************************************************/
color_t text2color(char input_text[])
{
    if(strcmp(input_text, AZUL_TEXT) == 0)
    {
        return AZUL;
    }
    else if(strcmp(input_text, AMARELO_TEXT) == 0)
    {
        return AMARELA;
    }
    else if(strcmp(input_text, ANIL_TEXT) == 0)
    {
        return ANIL;
    }
    else if(strcmp(input_text, PRETA_TEXT) == 0)
    {
        return PRETA;
    }
    else if(strcmp(input_text, BRANCA_TEXT) == 0)
    {
        return BRANCA;
    }
    else if(strcmp(input_text, VERDE_TEXT) == 0)
    {
        return VERDE;
    }
    else if(strcmp(input_text, VERMELHO_TEXT) == 0)
    {
        return VERMELHO;
    }
    else if(strcmp(input_text, LILAS_TEXT) == 0)
    {
        return LILAS;
    }
    else if(strcmp(input_text, ROSA_TEXT) == 0)
    {
        return ROSA;
    }
    else if(strcmp(input_text, LARANJA_TEXT) == 0)
    {
        return LARANJA;
    }

    return NO_COLOR;
}

/** ****************************************************************************
* Function : color2text()
* @description: Converts the input text into a color_t type
* @note:        Here the input_text must be similar to "az"
* @return 		color_t object
*******************************************************************************/
void color2text(color_t color_temp, char * temp_text)
{
    switch (color_temp) 
    {
        case AZUL:
            strcpy(temp_text, AZUL_TEXT);
        break;

        case AMARELA:
            strcpy(temp_text, AMARELO_TEXT);
        break;

        case ANIL:
            strcpy(temp_text, ANIL_TEXT);
        break;

        case PRETA:
            strcpy(temp_text, PRETA_TEXT);
        break;

        case BRANCA:
            strcpy(temp_text, BRANCA_TEXT);
        break;

        case VERDE:
            strcpy(temp_text, VERDE_TEXT);
        break;

        case VERMELHO:
            strcpy(temp_text, VERMELHO_TEXT);
        break;

        case LILAS:
            strcpy(temp_text, LILAS_TEXT);
        break;

        case ROSA:
            strcpy(temp_text, ROSA_TEXT);
        break;

        case LARANJA:
            strcpy(temp_text, LARANJA_TEXT);
        break;

        default:
        break;
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/