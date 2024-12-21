#include <stdlib.h>
#include <string.h>
#include "matrix.h"

static int is_unique(matrix_t *matrix, char *line, int *ind)
{
    for (size_t i = 0; i < matrix->size; i++)
    {
        if (strcmp(line, matrix->data[i]) == 0)
        {
            *ind = i;
            return NOT_UNIQUE;
        }
    }
    *ind = -1;
    return UNIQUE;
}

void free_matrix(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->size; i++)
        free(matrix->data[i]);
    free(matrix->data);
    matrix->data = NULL;
    matrix->size = 0;
}

void matrix_init(matrix_t *matrix)
{
    matrix->data = NULL;
    matrix->size = 0;
}

static int line_scan(FILE *file, char **out_line, size_t *line_size)
{
    char *line = NULL;
    size_t size;
    ssize_t res;
    res = getline(&line, &size, file);

    if (res == -1)
    {
        if (feof(file))
        {
            free(line);
            return END_OF_FILE;
        }
        else 
        {
            free(line);
            return INPUT_ERR;
        }
    }

    line[strlen(line) - 1] = '\0';
    *out_line = line;
    *line_size = size; 

    return OK;
}

int matrix_fscan(matrix_t *matrix, FILE *file, int **table)
{
    int res = 0;
    size_t temp_size = 0;
    char *temp_line = NULL;
    int unique, ind;
    char **new_data = NULL;
    int *new_table = NULL;

    res = line_scan(file, &temp_line, &temp_size);

    while (res == OK)
    {
        unique = is_unique(matrix, temp_line, &ind);

        if (unique == UNIQUE)
        {
            new_data = realloc(matrix->data, sizeof(char *) * (matrix->size + 1));
            if (!new_data) 
            {
                free(temp_line);
                free_matrix(matrix);
                return MALLOC_ERR;
            }
            matrix->data = new_data;
            matrix->data = new_data;
            
            matrix->data[matrix->size] = temp_line;
            temp_line = NULL;

            new_table = realloc(*table, sizeof(int) * (matrix->size + 1));
            if (!new_table)
            {
                free_matrix(matrix);
                return MALLOC_ERR;
            }
            *table = new_table;
            (*table)[matrix->size] = 1;
            matrix->size++;
        }
        else
        {
            (*table)[ind]++;
            free(temp_line);
            temp_line = NULL;
        }

        res = line_scan(file, &temp_line, &temp_size);
    }

    free(temp_line);
    
    if (res == END_OF_FILE)
        return OK;
    else
        return res;
}



void bubble_sort(matrix_t *matrix, int *table)
{
    char * temp;
    int int_temp;
    for (size_t i = 0; i < matrix->size; i++)
    {
        for (int j = 0; j < matrix->size - i - 1; j++)
        {
            if (strcmp(matrix->data[j], matrix->data[j + 1]) > 0)
            {
                temp = matrix->data[j];
                matrix->data[j] = matrix->data[j + 1];
                matrix->data[j + 1] = temp;

                int_temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = int_temp;
            }
        }
    }
}

void matrix_fprint(FILE *file, matrix_t *matrix, int *table)
{
    for (size_t i = 0; i < matrix->size; i++)
        fprintf(file, "%s: %d\n", matrix->data[i], table[i]);
}
