#ifndef _MATRIX_H__
#define _MATRIX_H__

#include <stdio.h>

#define OK 0
#define END_OF_FILE 1
#define INPUT_ERR 2
#define MALLOC_ERR 3
#define OPEN_ERR 4

#define NOT_UNIQUE 0
#define UNIQUE 1

typedef struct {
    char **data;
    size_t size;
} matrix_t;

void matrix_init(matrix_t *matrix);

int matrix_fscan(matrix_t *matrix, FILE *file, int **table);

void free_matrix(matrix_t *matrix);

void bubble_sort(matrix_t *matrix, int *table);

void matrix_fprint(FILE *file, matrix_t *matrix, int *table);

#endif
