/****************************************************************************
* Title                 :   aplicacao
* Filename              :   aplicacao.h
* Author                :   Gabriel Tomio
* Origin Date           :   01/05/2023
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

#include "stack_public.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define MAX_NUMBER_OF_STACKS    NUM_OF_COLORS
#define MAXIMUM_SIZE_OF_LINE    1000
#define FINISHED_ERROR          1
#define FINISHED_SUCCESS        0
#define MAX_IMPOSSIBLE_MOVES    20

/* Piece attributes */
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
#define SIZE_OF_COLOR_TEXT  2

#define STACK_TOKEN         "PC"
#define SIZE_OF_STACK_TOKEN 2

#define PIECE_TOKEN         "p"
#define SIZE_OF_PIECE_TOKEN 1

/* Stack Attributes */
#define TEMP_STACK_IDX      0


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/

	
/******************************************************************************
* Typedefs
*******************************************************************************/
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

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
color_t text2color(char input_text[]);
piece_t text2piece(char input_text[]);
colored_stack_t text2coloredstack(char input_text[]);

#endif
/*** End of File **************************************************************/