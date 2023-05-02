#include "aplicacao.h"

typedef enum {NO_COLOR, AZUL, AMARELA, ANIL, PRETA, BRANCA, VERDE, VERMELHO, LILAS, ROSA, LARANJA, NUM_OF_COLORS} color_t;

typedef struct
{
    color_t color;
    int size;
}piece_t;

typedef struct 
{
    p_stack_t stack_id;
    color_t color;
}colored_stack_t;


#define MAX_NUMBER_OF_STACKS    NUM_OF_COLORS
#define MAXIMUM_SIZE_OF_LINE    1000
#define FINISHED_ERROR          1
#define FINISHED_SUCCESS        0

#define MAX_IMPOSSIBLE_MOVES    20

#define AZUL_TEXT           "az"
#define AMARELO_TEXT        "am"
#define ANIL_TEXT           "an"
#define PRETA_TEXT          "pr"
#define BRANCA_TEXT         "br"
#define VERDE_TEXT          "ve"
#define VERMELHO_TEXT       "vo"
#define LILAS_TEXT          "li"
#define ROSA_TEXT           "ro"
#define LARANJA_TEXT        "lj"
#define SIZE_OF_COLOR_TEXT  strlen(AZUL_TEXT)

#define STACK_TOKEN         "PC"
#define SIZE_OF_STACK_TOKEN strlen(STACK_TOKEN)

#define PIECE_TOKEN         "p"
#define SIZE_OF_PIECE_TOKEN strlen(PIECE_TOKEN)

#define TEMP_STACK_IDX      0

color_t text2color(char input_text[]);
piece_t text2piece(char input_text[]);
colored_stack_t text2coloredstack(char input_text[]);

colored_stack_t * p_colored_stack[MAX_NUMBER_OF_STACKS];
int stack_size[MAX_NUMBER_OF_STACKS];

int main(int argc, char **argv)
{
    char line[MAXIMUM_SIZE_OF_LINE];
    int line_counter = 0;
    int temp_stack_size = 0;
    int colored_stack_idx = 0;
    int num_of_stacks = 0;

    printf("line_counter = %d\n", line_counter);

    while((fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL))
    {
        line_counter++;
        printf("line_counter = %d\n", line_counter);
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

            if(piece_start_index != piece_stop_index-1) // checks if the list is empty
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

                char piece_info_text[SIZE_OF_PIECE_TOKEN + SIZE_OF_COLOR_TEXT];
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
    printf("num_of_stacks = %d\n", num_of_stacks);

    // piece_t current_piece2; // todo: remove
    // for (int stackkkkkk_idx = 1; stackkkkkk_idx < 7; stackkkkkk_idx++)
    // {
    //     printf("stack:%d\n", stackkkkkk_idx);
    //     for (int piece_idx = 0; piece_idx < stack_size[stackkkkkk_idx]; piece_idx++)
    //     {
    //         stack_pop(p_colored_stack[stackkkkkk_idx]->stack_id, (void*) &current_piece2);
    //         printf("piece color: %d; size: %d\n", current_piece2.color, current_piece2.size);
    //     }
    // }
    
    
    // TODO: HERE COMES THE VERIFICATION IF A SOLUTION EXISTS
    
    // Algorithm initialization
    int expected_piece_size[MAX_NUMBER_OF_STACKS];
    expected_piece_size[TEMP_STACK_IDX] = 0; // TEMP STACK DOESN'T NEED THIS

    for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
    {
        expected_piece_size[stack_idx] = stack_size[stack_idx];
        printf("expected_piece_size = %d\n", expected_piece_size[stack_idx]);
    }
    
    // Unstack Algorithm
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
                            b_no_possible_moves_flag = 0;
                            expected_piece_size[stack_idx_2]--;
                            stack_pop(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece);
                            stack_push(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece);
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
                if(++empty_stack_count >= (num_of_stacks-1))
                {
                    b_stack_temp_finished = 1;
                    break;
                }
            }
        }
    }

    /* Unstack the pieces stored on the temporary stack onto their correct stack colors */
    for(int piece_idx = 0; piece_idx < stack_size[TEMP_STACK_IDX]; piece_idx++)
    {
        if(stack_pop(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece) != STACK_ERROR)
        {
            for (int stack_idx = 1; stack_idx <= num_of_stacks; stack_idx++)
            {
                if(current_piece.color == p_colored_stack[stack_idx]->color)
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

    // TODO: REMOVE THIS DEBUG SECTION
    piece_t current_piece2; // todo: remove
    for (int stackkkkkk_idx = 1; stackkkkkk_idx < 7; stackkkkkk_idx++)
    {
        printf("stack:%d\n", stackkkkkk_idx);
        for (int piece_idx = 0; piece_idx < stack_size[stackkkkkk_idx]; piece_idx++)
        {
            stack_pop(p_colored_stack[stackkkkkk_idx]->stack_id, (void*) &current_piece2);
            printf("piece color: %d; size: %d\n", current_piece2.color, current_piece2.size);
        }
    }
    //////////////////////////////////
    
    for (int stack_idx = 0; stack_idx <= num_of_stacks; stack_idx++)
    {
        stack_destroy(&(*p_colored_stack[stack_idx]).stack_id);
    }

    return 0;
}

// AQUI EU RECEBO SÓ O "PCaz"
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

// AQUI EU RECEBO SÓ O "paz1"
piece_t text2piece(char input_text[])
{
    piece_t temp_piece;
    char temp_piece_color[SIZE_OF_COLOR_TEXT + 1];
    char temp_piece_size[strlen(input_text) - SIZE_OF_COLOR_TEXT - strlen(PIECE_TOKEN) + 1];

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_piece_color[i] = input_text[i + strlen(PIECE_TOKEN)];
    }
    temp_piece.color = text2color(temp_piece_color);

    for (int i = 0; i < strlen(temp_piece_size); i++)
    {
        temp_piece_size[i] = input_text[SIZE_OF_COLOR_TEXT + strlen(PIECE_TOKEN) + i];
    }
    temp_piece.size = atoi(temp_piece_size);
    
    return temp_piece;
}

// AQUI EU RECEBO SÓ O "az"
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