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

colored_stack_t * p_colored_stack[NUM_OF_COLORS];
piece_t * p_colored_stack_init[NUM_OF_COLORS];
int stack_size[NUM_OF_STACKS] = {TEMP_SIZE, PCAZ_SIZE, PCAN_SIZE, PCLI_SIZE, PCVE_SIZE, PCVO_SIZE, PCAM_SIZE};

int main(int argc, char **argv)
{
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

    /* OK TESTED */
    for (int stack_idx = 0; stack_idx < num_of_stacks; stack_idx++)
    {
        stack_create(&(p_colored_stack[stack_idx]->stack_id), sizeof(piece_t), stack_size[stack_idx]);
    }

    /* OK TESTED */
    for (int stack_idx = 1; stack_idx < num_of_stacks; stack_idx++) // it starts from 1 to do not use the temp stack
    {
        for (int data_idx = 0; data_idx < stack_size[stack_idx]; data_idx++)
        {
            stack_push(p_colored_stack[stack_idx]->stack_id, (void *)&((p_colored_stack_init[stack_idx])[data_idx]));
        }
    }

    // TODO: HERE COMES THE VERIFICATION IF A SOLUTION EXISTS
    
    // Algorithm initialization
    int expected_piece_size[NUM_OF_STACKS]; // todo: talvez depois seja preciso alocar o máximo possível de stacks
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
                    if (current_piece.color == p_colored_stack[stack_idx_2]->color)
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