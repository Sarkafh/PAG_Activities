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

color_t text2color(char input_text[]);
piece_t text2piece(char input_text[]);
colored_stack_t text2coloredstack(char input_text[]);

// N=6;
// Pt=[];
// PCaz=[pli1;paz2;paz3;paz7;paz8;pan1;pam2;pam3];
// PCan=[pam4;pan2;pan3;pan4;pan5;pan6;pan7;pan8];
// PCli=[paz1;pli2;pli3;pli4;pli5;pli6;pli7;pli8];
// PCve=[pve1;pve4;pvo2;pvo3;pve5];
// PCvo=[pvo1;pve2;pve3;pvo4];
// PCam=[pam1;paz4;paz5;paz6];

/* DEBUG CONFIGURATIONS!! */
#define PCAZ_SIZE   8
#define PCAN_SIZE   8
#define PCLI_SIZE   8
#define PCVE_SIZE   5
#define PCVO_SIZE   4
#define PCAM_SIZE   4

#define TEMP_SIZE   (PCAZ_SIZE + PCAN_SIZE + PCLI_SIZE + PCVE_SIZE + PCVO_SIZE + PCAM_SIZE)

#define paz1  {AZUL, 1}
#define paz2  {AZUL, 2}
#define paz3  {AZUL, 3}
#define paz4  {AZUL, 4}
#define paz5  {AZUL, 5}
#define paz6  {AZUL, 6}
#define paz7  {AZUL, 7}
#define paz8  {AZUL, 8}

#define pan1  {ANIL, 1}
#define pan2  {ANIL, 2}
#define pan3  {ANIL, 3}
#define pan4  {ANIL, 4}
#define pan5  {ANIL, 5}
#define pan6  {ANIL, 6}
#define pan7  {ANIL, 7}
#define pan8  {ANIL, 8}

#define pli1  {LILAS, 1}
#define pli2  {LILAS, 2}
#define pli3  {LILAS, 3}
#define pli4  {LILAS, 4}
#define pli5  {LILAS, 5}
#define pli6  {LILAS, 6}
#define pli7  {LILAS, 7}
#define pli8  {LILAS, 8}

#define pve1  {VERDE, 1}
#define pve2  {VERDE, 2}
#define pve3  {VERDE, 3}
#define pve4  {VERDE, 4}
#define pve5  {VERDE, 5}

#define pvo1  {VERMELHO, 1}
#define pvo2  {VERMELHO, 2}
#define pvo3  {VERMELHO, 3}
#define pvo4  {VERMELHO, 4}

#define pam1  {AMARELA, 1}
#define pam2  {AMARELA, 2}
#define pam3  {AMARELA, 3}
#define pam4  {AMARELA, 4}


#define NUM_OF_STACKS 7
#define TEMP_STACK_IDX 0
int N=6;
piece_t PCaz_init[] = {pli1,paz2,paz3,paz7,paz8,pan1,pam2,pam3};
piece_t PCan_init[] = {pam4,pan2,pan3,pan4,pan5,pan6,pan7,pan8};
piece_t PCli_init[] = {paz1,pli2,pli3,pli4,pli5,pli6,pli7,pli8};
piece_t PCve_init[] = {pve1,pve4,pvo2,pvo3,pve5};
piece_t PCvo_init[] = {pvo1,pve2,pve3,pvo4};
piece_t PCam_init[] = {pam1,paz4,paz5,paz6};

colored_stack_t * p_colored_stack[MAX_NUMBER_OF_STACKS];
piece_t * p_colored_stack_init[NUM_OF_COLORS];
int stack_size[NUM_OF_STACKS] = {TEMP_SIZE, PCAZ_SIZE, PCAN_SIZE, PCLI_SIZE, PCVE_SIZE, PCVO_SIZE, PCAM_SIZE};

int main(int argc, char **argv)
{
    char line[MAXIMUM_SIZE_OF_LINE];
    int line_counter = 0;
    int temp_stack_size = 0;
    int colored_stack_idx = 0;

    while(fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL)
    {
        line_counter++;
        if (line_counter == 1)
        {
            
        }
        else if (line_counter == 2)
        {

        }
        else
        {
            /* Find stack color */
            char stack_color_text[SIZE_OF_STACK_TOKEN + SIZE_OF_COLOR_TEXT];

            for (int i = 0; i < strlen(stack_color_text); i++)
            {
                stack_color_text[i] = line[i];
            }

            *p_colored_stack[colored_stack_idx] = text2coloredstack(stack_color_text);

            int piece_start_index = 0;
            int piece_stop_index = 0;

            for (int i = 0; i < strlen(line); i++)
            {
                if(line[i] == "[")
                {
                    piece_start_index = i;
                }
                else if (line[i] == "]")
                {
                    piece_stop_index = i;
                    break;
                }
            }

            if(piece_start_index == piece_stop_index-1) // checks if the list is empty
            {
                int size_of_current_stack = 1; // It starts in one to count the last piece
                for (int i = piece_start_index + 1; i < piece_stop_index; i++)
                {
                    if(line[i] == ";")
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
                    if(line[i] == ";")
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
            colored_stack_idx++;
        }
        
    }




    int num_of_stacks = NUM_OF_STACKS;
    
    colored_stack_t temp_stack;
    colored_stack_t PCaz;
    colored_stack_t PCan;
    colored_stack_t PCli;
    colored_stack_t PCve;
    colored_stack_t PCvo;
    colored_stack_t PCam;

    PCaz.color = AZUL;
    PCan.color = ANIL;
    PCli.color = LILAS;
    PCve.color = VERDE;
    PCvo.color = VERMELHO;
    PCam.color = AMARELA;
    temp_stack.color = NO_COLOR;

    // p_colored_stack_init[0] = &temp_stack;
    p_colored_stack_init[1] = PCaz_init;
    p_colored_stack_init[2] = PCan_init;
    p_colored_stack_init[3] = PCli_init;
    p_colored_stack_init[4] = PCve_init;
    p_colored_stack_init[5] = PCvo_init;
    p_colored_stack_init[6] = PCam_init;


    p_colored_stack[0] = &temp_stack;
    p_colored_stack[1] = &PCaz;
    p_colored_stack[2] = &PCan;
    p_colored_stack[3] = &PCli;
    p_colored_stack[4] = &PCve;
    p_colored_stack[5] = &PCvo;
    p_colored_stack[6] = &PCam;

    for (int stack_idx = 0; stack_idx < num_of_stacks; stack_idx++)
    {
        stack_create(&(p_colored_stack[stack_idx]->stack_id), sizeof(piece_t), stack_size[stack_idx]);
    }

    for (int stack_idx = 1; stack_idx < num_of_stacks; stack_idx++) // it starts from 1 to do not use the temp stack
    {
        for (int data_idx = 0; data_idx < stack_size[stack_idx]; data_idx++)
        {
            stack_push(p_colored_stack[stack_idx]->stack_id, (void *)&((p_colored_stack_init[stack_idx])[data_idx]));
        }
    }

    // TODO: HERE COMES THE VERIFICATION IF A SOLUTION EXISTS
    
    // Algorithm initialization
    int expected_piece_size[MAX_NUMBER_OF_STACKS]; // todo: talvez depois seja preciso alocar o máximo possível de stacks
    expected_piece_size[0] = 0; // TEMP STACK DOESN'T NEED THIS

    for (int stack_idx = 1; stack_idx < num_of_stacks; stack_idx++)
    {
        expected_piece_size[stack_idx] = stack_size[stack_idx];
    }

    // Unstack Algorithm
    int b_stack_temp_finished = 0;
    piece_t current_piece;
    int empty_stack_count = 0;

    /* Store pieces on the temporary stack */
    while (b_stack_temp_finished == 0)
    {
        for (int stack_idx = 1; stack_idx < num_of_stacks; stack_idx++)
        {
            if(stack_top(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece) != STACK_ERROR)
            {
                empty_stack_count = 0;
                for (int stack_idx_2 = 1; stack_idx_2 < num_of_stacks; stack_idx_2++)
                {
                    if (current_piece.color == p_colored_stack[stack_idx_2]->color) /* find index to current piece color */
                    {
                        if(current_piece.size == expected_piece_size[stack_idx_2])
                        {
                            expected_piece_size[stack_idx_2]--;
                            stack_pop(p_colored_stack[stack_idx]->stack_id, (void*) &current_piece);
                            stack_push(p_colored_stack[TEMP_STACK_IDX]->stack_id, (void*) &current_piece);
                        }
                        // TODO: COLOCAR UM CHECK SE NÃO HÁ MAIS MOVIMENTOS VÁLIDOS
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
            for (int stack_idx = 1; stack_idx < num_of_stacks; stack_idx++)
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
    for (int piece_idx = 0; piece_idx < 4; piece_idx++)
    {
        stack_pop(p_colored_stack[6]->stack_id, (void*) &current_piece);
        printf("piece color: %d; size: %d\n", current_piece.color, current_piece.size);
    }
    //////////////////////////////////
    
    for (int stack_idx = 0; stack_idx < num_of_stacks; stack_idx++)
    {
        stack_destroy(&(*p_colored_stack[stack_idx]).stack_id);
    }

    return 0;
}

// AQUI EU RECEBO SÓ O "PCaz"
colored_stack_t text2coloredstack(char input_text[])
{
    colored_stack_t temp_colored_stack;
    char temp_stack_color[SIZE_OF_COLOR_TEXT];

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_stack_color[i] = input_text[i + strlen(STACK_TOKEN)];
    }

    temp_colored_stack.color = text2color(temp_stack_color);

    return temp_colored_stack;
}

// AQUI EU RECEBO SÓ O "paz1"
piece_t text2piece(char input_text[])
{
    piece_t temp_piece;
    char temp_piece_color[SIZE_OF_COLOR_TEXT];
    char temp_piece_size[strlen(input_text) - SIZE_OF_COLOR_TEXT - strlen(PIECE_TOKEN)];

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_piece_color[i] = input_text[i + strlen(PIECE_TOKEN)];
    }
    temp_piece.color = text2color(input_text);

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