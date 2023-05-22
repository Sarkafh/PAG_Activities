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
    char line[MAXIMUM_SIZE_OF_LINE];
    char * p_new_line;
    int line_counter = 0;
    int delimiter_counter = 0;
    int raw_material_idx = -1;
    int finished_piece_counter = 0;
    int defective_piece_counter = 0;
    colored_queue_t cast_queue;
    colored_queue_t finished_pieces;
    colored_queue_t defective_pieces;

    colored_queue_t * raw_material_queue[NUM_OF_COLORS];

    

    queue_create(&finished_pieces.queue_id, sizeof(finished_piece_t), MAX_NUMBER_CASTS);
    queue_create(&defective_pieces.queue_id, sizeof(defective_piece_t), NUM_OF_COLORS*MAX_NUMBER_MATERIAL);
    queue_create(&cast_queue.queue_id, sizeof(cast_t), MAX_NUMBER_CASTS);


    while (fgets(line, MAXIMUM_SIZE_OF_LINE, stdin) != NULL)
    {
        line_counter++;
        if (line_counter != 1) /* Ignore first element */
        {
            delimiter_counter = 0;
            p_new_line = strtok(line, DELIMITER_CHARACTER);

            while ((p_new_line != NULL) && (strcmp(p_new_line, "\n") != 0) && (strcmp(p_new_line, "]") != 0))
            {
                delimiter_counter++;
                if(line_counter == 2)
                {
                    if(delimiter_counter == 1) /* First delimiter is the queue definition */
                    {
                        cast_queue.color = NO_COLOR;
                    }
                    else
                    {
                        cast_t new_cast;
                        new_cast = text2cast(p_new_line);
                        queue_enqueue(cast_queue.queue_id, &new_cast);
                    }
                }
                else
                {
                    if(delimiter_counter == 1) /* First delimiter is the queue definition */
                    {
                        colored_queue_t temp_queue;
                        temp_queue = text2coloredqueue(p_new_line);
                        raw_material_idx++;
                        raw_material_queue[raw_material_idx] = (colored_queue_t*) malloc(sizeof(colored_queue_t));
                        queue_create(&raw_material_queue[raw_material_idx]->queue_id, sizeof(raw_material_t), MAX_NUMBER_MATERIAL);
                        raw_material_queue[raw_material_idx]->color = temp_queue.color;
                    }
                    else
                    {
                        raw_material_t new_raw_material;
                        new_raw_material = text2rawmaterial(p_new_line);
                        queue_enqueue(raw_material_queue[raw_material_idx]->queue_id, &new_raw_material);
                    }
                }
                p_new_line = strtok(NULL, DELIMITER_CHARACTER);
            }
        }
    }

    int num_of_raw_materials;
    int num_of_casts;

    num_of_raw_materials = raw_material_idx + 1;
    queue_current_size(cast_queue.queue_id, &num_of_casts);

    for (int cast_i = 0; cast_i < num_of_casts; cast_i++)
    {
        cast_t current_cast;
        raw_material_t current_raw_material;
        queue_dequeue(cast_queue.queue_id, &current_cast);
        for (int raw_mat_idx = 0; raw_mat_idx < num_of_raw_materials; raw_mat_idx++)
        {
            if(current_cast.color == raw_material_queue[raw_mat_idx]->color)
            {
                int qtd_of_mat;
                queue_current_size(raw_material_queue[raw_mat_idx]->queue_id, &qtd_of_mat);
                if (qtd_of_mat == 0)
                {
                    int highest_raw_mat_count = 0;
                    int highest_raw_mat_count_idx = 0;
                    for (int i = 0; i < num_of_raw_materials; i++)
                    {
                        int qtd_mat_temp = 0;
                        queue_current_size(raw_material_queue[i]->queue_id, &qtd_mat_temp);
                        if(qtd_mat_temp > highest_raw_mat_count)
                        {
                            highest_raw_mat_count = qtd_mat_temp;
                            highest_raw_mat_count_idx = i;
                        }
                    }
                    raw_mat_idx = highest_raw_mat_count_idx;
                }
                
                queue_dequeue(raw_material_queue[raw_mat_idx]->queue_id, &current_raw_material);
                break;
            }
        }
        if (current_raw_material.color == current_cast.color)
        {
            finished_piece_counter++;

            finished_piece_t finished_piece_temp;

            finished_piece_temp.color = current_cast.color;
            finished_piece_temp.identifier = finished_piece_counter;
            queue_enqueue(finished_pieces.queue_id, &finished_piece_temp);
        }
        else
        {
            defective_piece_counter++;

            defective_piece_t defective_piece_temp;

            defective_piece_temp.color = NO_COLOR;
            defective_piece_temp.identifier = defective_piece_counter;
            queue_enqueue(defective_pieces.queue_id, &defective_piece_temp);
        }
    }

    for (int raw_mat_idx = 0; raw_mat_idx < num_of_raw_materials; raw_mat_idx++)
    {
        int current_qty_of_materials;
        queue_current_size(raw_material_queue[raw_mat_idx]->queue_id, &current_qty_of_materials);

        if (current_qty_of_materials > 0)
        {
            for (int i = 0; i < current_qty_of_materials; i++)
            {
                raw_material_t current_raw_material;
                defective_piece_t defective_piece_temp;
                queue_dequeue(raw_material_queue[raw_mat_idx]->queue_id, &current_raw_material);
                defective_piece_counter++;
                defective_piece_temp.color = NO_COLOR;
                defective_piece_temp.identifier = defective_piece_counter;
                queue_enqueue(defective_pieces.queue_id, &defective_piece_temp);
            }
        }
    }
    

    int defective_pieces_queue_size;
    int finished_pieces_queue_size;

    char * print_text;
    print_text = (char *)malloc(10*sizeof(char));

    queue_current_size(defective_pieces.queue_id, &defective_pieces_queue_size);
    queue_current_size(finished_pieces.queue_id, &finished_pieces_queue_size);
    
    printf("PC=[;");
    for (int finished_piece_idx = 0; finished_piece_idx < finished_pieces_queue_size; finished_piece_idx++)
    {
        finished_piece_t current_finished_piece;
        queue_dequeue(finished_pieces.queue_id, &current_finished_piece);
        finishedpiecepiece2text(current_finished_piece, print_text);
        printf("%s;", print_text);
    }
    printf("]\n");

    printf("PD=[;");
    for (int defective_piece_idx = 0; defective_piece_idx < defective_pieces_queue_size; defective_piece_idx++)
    {
        defective_piece_t current_defective_piece;
        queue_dequeue(defective_pieces.queue_id, &current_defective_piece);
        defectivepiece2text(current_defective_piece, print_text);
        printf("%s;", print_text);
    }
    printf("]\n");
    

    for (int queue_idx = 0; queue_idx < num_of_raw_materials; queue_idx++)
    {
        queue_destroy(&raw_material_queue[queue_idx]->queue_id);
    }
    queue_destroy(&finished_pieces.queue_id);
    queue_destroy(&defective_pieces.queue_id);
    queue_destroy(&cast_queue.queue_id);

    return FINISHED_SUCCESS;
}

/** ****************************************************************************
* Function : text2coloredqueue()
* @description: Converts the input text into a colored_queue_t type
* @note:        Here the input_text must be similar to "PCaz"
* @return 		colored_queue_t object
*******************************************************************************/
colored_queue_t text2coloredqueue(char input_text[])
{
    char temp_queue_color[] = AZUL_TEXT;
    colored_queue_t temp_colored_queue = (colored_queue_t){(p_queue_t)0, NO_COLOR};
    color_t temp_color;

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_queue_color[i] = input_text[i + strlen(QUEUE_TOKEN)];
    }

    temp_color = text2color(temp_queue_color);
    temp_colored_queue.color = temp_color;

    return temp_colored_queue;
}


/** ****************************************************************************
* Function : defectivepiece2text()
* @description: Converts the input text into a colored_queue_t type
* @note:        Here the input_text must be similar to "PCaz"
* @return 		colored_queue_t object
*******************************************************************************/
void defectivepiece2text(defective_piece_t defective_piece_temp, char * temp_text)
{
    char color_text[SIZE_OF_COLOR_TEXT +1];
    char piece_size_text[10];
    int text_offset=0;
    
    for (int i = 0; i < SIZE_OF_DEFECTIVE_PIECE_TOKEN; i++)
    {
        temp_text[i] = DEFECTIVE_PIECE_TOKEN[i];
    }

    text_offset = SIZE_OF_DEFECTIVE_PIECE_TOKEN;

    for (int i = 0; i < SIZE_OF_COLOR_NUMBER_SEPARATOR; i++)
    {
        temp_text[i+text_offset] = COLOR_NUMBER_SEPARATOR[i];
    }

    text_offset += SIZE_OF_COLOR_NUMBER_SEPARATOR;

    sprintf(piece_size_text, "%d", defective_piece_temp.identifier);
    // itoa(defective_piece_temp.identifier, piece_size_text, 10);
    for (int i = 0; i < strlen(piece_size_text); i++)
    {
        temp_text[i+text_offset] = piece_size_text[i];
    }

    text_offset += strlen(piece_size_text);
    temp_text[text_offset] = '\0';
}

/** ****************************************************************************
* Function : coloredqueue2text()
* @description: Converts the input text into a colored_queue_t type
* @note:        Here the input_text must be similar to "PCaz"
* @return 		colored_queue_t object
*******************************************************************************/
void finishedpiecepiece2text(finished_piece_t finished_piece_temp, char * temp_text)
{
    char color_text[SIZE_OF_COLOR_TEXT +1];
    char piece_size_text[10];
    int text_offset=0;

    for (int i = 0; i < SIZE_OF_FINISHED_PIECE_TOKEN; i++)
    {
        temp_text[i] = FINISHED_PIECE_TOKEN[i];
    }
    text_offset = SIZE_OF_FINISHED_PIECE_TOKEN;


    color2text(finished_piece_temp.color, color_text);

    for (int i = 0; i < strlen(color_text); i++)
    {
        temp_text[i+text_offset] = color_text[i];
    }

    text_offset += strlen(color_text);

    for (int i = 0; i < SIZE_OF_COLOR_NUMBER_SEPARATOR; i++)
    {
        temp_text[i+text_offset] = COLOR_NUMBER_SEPARATOR[i];
    }

    text_offset += SIZE_OF_COLOR_NUMBER_SEPARATOR;
    sprintf(piece_size_text, "%d", finished_piece_temp.identifier);
    // itoa(defective_piece_temp.identifier, piece_size_text, 10);
    for (int i = 0; i < strlen(piece_size_text); i++)
    {
        temp_text[i+text_offset] = piece_size_text[i];
    }

    text_offset += strlen(piece_size_text);
    temp_text[text_offset] = '\0';
}


/** ****************************************************************************
* Function : text2cast()
* @description: Converts the input text into a cast_t type
* @note:        Here the input_text must be similar to "maz_1"
* @return 		cast_t object
*******************************************************************************/
cast_t text2cast(char input_text[])
{
    cast_t temp_cast;
    char temp_cast_color[] = AZUL_TEXT;
    char temp_cast_identifier[strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_CAST_TOKEN];
    int piece_identifier_size = strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_CAST_TOKEN;

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_cast_color[i] = input_text[i + strlen(CAST_TOKEN)];
    }
    temp_cast.color = text2color(temp_cast_color);

    for (int i = 0; i < piece_identifier_size; i++)
    {
        temp_cast_identifier[i] = input_text[SIZE_OF_COLOR_TEXT + SIZE_OF_CAST_TOKEN + i];
    }
    temp_cast.identifier = atoi(temp_cast_identifier);
    
    return temp_cast;
}

/** ****************************************************************************
* Function : text2rawmaterial()
* @description: Converts the input text into a cast_t type
* @note:        Here the input_text must be similar to "paz1"
* @return 		cast_t object
*******************************************************************************/
raw_material_t text2rawmaterial(char input_text[])
{
    raw_material_t temp_raw_material;
    char temp_raw_mat_color[] = AZUL_TEXT;
    char temp_raw_mat_identifier[strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_CAST_TOKEN];
    int piece_identifier_size = strlen(input_text) - SIZE_OF_COLOR_TEXT - SIZE_OF_CAST_TOKEN;

    for (int i = 0; i < SIZE_OF_COLOR_TEXT; i++)
    {
        temp_raw_mat_color[i] = input_text[i + strlen(CAST_TOKEN)];
    }
    temp_raw_material.color = text2color(temp_raw_mat_color);

    for (int i = 0; i < piece_identifier_size; i++)
    {
        temp_raw_mat_identifier[i] = input_text[SIZE_OF_COLOR_TEXT + SIZE_OF_CAST_TOKEN + i];
    }
    temp_raw_material.identifier = atoi(temp_raw_mat_identifier);
    
    return temp_raw_material;
}

/** ****************************************************************************
* Function : cast2text()
* @description: Converts the input text into a cast_t type
* @note:        Here the input_text must be similar to "paz1"
* @return 		cast_t object
*******************************************************************************/
// void cast2text(cast_t cast_temp, char * temp_text)
// {
//     char color_text[SIZE_OF_COLOR_TEXT +1];
//     char piece_size_text[10];
//     int text_offset=0;

//     for (int i = 0; i < SIZE_OF_CAST_TOKEN; i++)
//     {
//         temp_text[i] = CAST_TOKEN[i];
//     }

//     text_offset = SIZE_OF_CAST_TOKEN;
//     color2text(cast_temp.color, color_text);

//     for (int i = 0; i < strlen(color_text); i++)
//     {
//         temp_text[i+text_offset] = color_text[i];
//     }

//     text_offset += strlen(color_text);
//     sprintf(piece_size_text, "%d", cast_temp.size);
//     // itoa(cast_temp.size, piece_size_text, 10);
//     for (int i = 0; i < strlen(piece_size_text); i++)
//     {
//         temp_text[i+text_offset] = piece_size_text[i];
//     }
// }

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