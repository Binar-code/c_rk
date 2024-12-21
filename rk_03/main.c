#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    if (!matrix)
        return MALLOC_ERR;
    matrix_init(matrix);

    int *table = NULL;
    FILE *file;
    int res;

    char *in_file = "in.txt";
    char *out_file = "out.txt";

    file = fopen(in_file, "r");
    if (!file)
    {
        free(matrix);
        return OPEN_ERR;
    }

    res = matrix_fscan(matrix, file, &table);
    fclose(file);

    if (res != OK)
    {
        free_matrix(matrix);
        free(matrix);
        free(table);
        return res;
    }

    bubble_sort(matrix, table);

    file = fopen(out_file, "w");

    if (!file)
        return OPEN_ERR;

    matrix_fprint(file, matrix, table);
    fclose(file);
    
    free_matrix(matrix);
    free(matrix);
    free(table);

    return OK;
}
