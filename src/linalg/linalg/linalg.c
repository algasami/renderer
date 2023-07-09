#include <linalg/linalg.h>
#include <stdio.h>
#include <stdlib.h>

void la_init_matrix(struct La_Matrix *ptr, size_t rows, size_t cols, enum LA_ELEM_TYPES t)
{
    ptr->rows = rows;
    ptr->cols = cols;
    ptr->t = t;
    switch (t)
    {
    case LA_FLOAT_T:
        ptr->buffer = calloc(rows * cols, sizeof(float));
        break;
    case LA_INT_T:
        ptr->buffer = calloc(rows * cols, sizeof(int));
        break;
    default:
        break;
    }
    // automatically resets to zero
}

void la_destroy_matrix(struct La_Matrix *ptr)
{
    free(ptr->buffer);
}

void la_print_matrix(struct La_Matrix *ptr)
{
    for (size_t i = 0; i < ptr->rows; i++)
    {
        printf("|\t");
        for (size_t j = 0; j < ptr->cols; j++)
            switch (ptr->t)
            {
            case LA_FLOAT_T:
                printf("%f\t", MATIND(*ptr, i, j, float));
                break;
            case LA_INT_T:
                printf("%d\t", MATIND(*ptr, i, j, int));
                break;
            default:
                break;
            }
        printf("|\n");
    }
}

void la_id_matrix(struct La_Matrix *ptr, size_t rowcols, enum LA_ELEM_TYPES t)
{
    la_init_matrix(ptr, rowcols, rowcols, t);
    for (size_t i = 0; i < rowcols; i++)
    {
        switch (t)
        {
        case LA_FLOAT_T:
            MATIND(*ptr, i, i, float) = 1.0f;
            break;
        case LA_INT_T:
            MATIND(*ptr, i, i, int) = 1;
            break;
        default:
            break;
        }
    }
}

int la_matrix_mul(struct La_Matrix *ptr_a, struct La_Matrix *ptr_b, struct La_Matrix *ptr_result)
{
    if (ptr_a->cols != ptr_b->rows || ptr_a->rows != ptr_result->rows || ptr_b->cols != ptr_result->cols)
        return -1;
    for (int i = 0; i < ptr_a->rows; i++)
    {
        for (int j = 0; j < ptr_b->cols; j++)
        {
            for (int k = 0; k < ptr_a->cols; k++)
            {
                switch (ptr_result->t)
                {
                case LA_FLOAT_T:
                    MATIND(*ptr_result, i, j, float) = MATIND(*ptr_a, i, k, float) * MATIND(*ptr_b, k, j, float);
                    break;
                case LA_INT_T:
                    MATIND(*ptr_result, i, j, int) = MATIND(*ptr_a, i, k, int) * MATIND(*ptr_b, k, j, int);
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
}

int la_matrix_pow(struct La_Matrix *ptr, unsigned int pow)
{
    return 0;
}