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

#include "queue_public.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define MAX_NUMBER_OF_STACKS    NUM_OF_COLORS
#define MAXIMUM_SIZE_OF_LINE    1000
#define FINISHED_ERROR          1
#define FINISHED_SUCCESS        0
#define MAX_NUMBER_CASTS        100
#define MAX_NUMBER_MATERIAL     100


#define DELIMITER_CHARACTER ";"

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

#define QUEUE_TOKEN         "FC"
#define SIZE_OF_QUEUE_TOKEN 2

#define RAW_MATERIAL_TOKEN         "m"
#define SIZE_OF_RAW_MATERIAL_TOKEN  1

#define CAST_TOKEN         "M"
#define SIZE_OF_CAST_TOKEN  1

#define COLOR_NUMBER_SEPARATOR  "_"
#define SIZE_OF_COLOR_NUMBER_SEPARATOR  1

#define DEFECTIVE_PIECE_TOKEN   "d"
#define SIZE_OF_DEFECTIVE_PIECE_TOKEN   1

#define FINISHED_PIECE_TOKEN    "p"
#define SIZE_OF_FINISHED_PIECE_TOKEN    1

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
// typedef enum {NO_COLOR, AZUL, AMARELA, ANIL, PRETA, BRANCA, VERDE, VERMELHO, LILAS, ROSA, LARANJA, NUM_OF_COLORS} color_t;
/* Enum em ordem alfabética */
typedef enum {NO_COLOR, AMARELA, ANIL, AZUL, BRANCA, LARANJA, LILAS, PRETA, ROSA, VERDE, VERMELHO, NUM_OF_COLORS} color_t;

typedef struct
{
    color_t color;
    int identifier;
}cast_t;

typedef struct
{
    color_t color;
    int identifier;
}raw_material_t;

typedef struct
{
    color_t color;
    int identifier;
}finished_piece_t;

typedef struct
{
    color_t color;
    int identifier;
}defective_piece_t;

typedef struct 
{
    p_queue_t queue_id;
    color_t color;
}colored_queue_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
color_t text2color(char input_text[]);
void color2text(color_t color_temp, char * temp_text);
cast_t text2cast(char input_text[]);
colored_queue_t text2coloredqueue(char input_text[]);
void coloredqueue2text(colored_queue_t colored_stack_temp, char * temp_text);
raw_material_t text2rawmaterial(char input_text[]);
void defectivepiece2text(defective_piece_t defective_piece_temp, char * temp_text);
void finishedpiecepiece2text(finished_piece_t finished_piece_temp, char * temp_text);

#endif
/*** End of File **************************************************************/