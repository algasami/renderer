// Linalg.h

#ifndef LINALG_H
#define LINALG_H

#define MATIND(m, i, j, t) ((t *)(m).buffer)[(i) * (m).cols + (j)]

#include <stddef.h>

enum LA_ELEM_TYPES
{
    LA_FLOAT_T = 0,
    LA_INT_T = 1,
};

struct La_Matrix
{
    size_t rows, cols;
    enum LA_ELEM_TYPES t;
    void *buffer;
};

void la_init_matrix(struct La_Matrix *ptr, size_t rows, size_t cols, enum LA_ELEM_TYPES t);
void la_destroy_matrix(struct La_Matrix *ptr);

void la_print_matrix(struct La_Matrix *ptr);

void la_id_matrix(struct La_Matrix *ptr, size_t rowcols, enum LA_ELEM_TYPES t);
int la_matrix_mul(struct La_Matrix *ptr_a, struct La_Matrix *ptr_b, struct La_Matrix *ptr_result);

int la_matrix_pow(struct La_Matrix *ptr, unsigned int pow);

#endif
