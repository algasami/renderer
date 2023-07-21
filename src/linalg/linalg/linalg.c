#include <linalg/linalg.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void la_init_matrix(struct La_Matrix *ptr, size_t rows, size_t cols, enum LA_ELEM_TYPES t)
{
    if (ptr->__inited == 1)
    {
        printf("la_init_matrix: matrix has been initialized!!!");
        return;
    }
    ptr->rows = rows;
    ptr->cols = cols;
    ptr->t = t;
    ptr->__inited = 1;
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
    ptr->__inited = 0;
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
    printf("\n");
}

void la_id_matrix(struct La_Matrix *ptr, size_t rowcols, enum LA_ELEM_TYPES t)
{
    if (ptr->__inited != 1)
    {
        la_init_matrix(ptr, rowcols, rowcols, t);
    }
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

int la_matrix_copy(struct La_Matrix *base, struct La_Matrix *dest)
{
    if (dest->__inited != 1)
    {
        la_init_matrix(dest, base->rows, base->cols, base->t);
    }

    if (dest->rows != base->rows || dest->cols != base->cols)
        return -1;
    for (int i = 0; i < base->rows; i++)
        for (int j = 0; j < base->cols; j++)
            switch (dest->t)
            {
            case LA_FLOAT_T:
                MATIND(*dest, i, j, float) = MATIND(*base, i, j, float);
                break;
            case LA_INT_T:
                MATIND(*dest, i, j, int) = MATIND(*base, i, j, int);
                break;
            default:
                break;
            }
    return 0;
}

inline void la_matrix_zero(struct La_Matrix *ptr)
{
    switch (ptr->t)
    {
    case LA_INT_T:
        memset(ptr->buffer, 0, sizeof(int) * ptr->rows * ptr->cols);
        break;
    case LA_FLOAT_T:
        memset(ptr->buffer, 0, sizeof(float) * ptr->rows * ptr->cols);
        break;
    default:
        break;
    }
}

int la_matrix_mul(struct La_Matrix *ptr_a, struct La_Matrix *ptr_b, struct La_Matrix *ptr_result)
{
    if (ptr_a->cols != ptr_b->rows || ptr_a->rows != ptr_result->rows || ptr_b->cols != ptr_result->cols)
        return -1;

    int enable_buffer = ptr_a == ptr_result || ptr_b == ptr_result;
    struct La_Matrix *target;
    if (enable_buffer)
    {
        printf("la_matrix_mul: ptr_result's address is identical to that of ptr_a or ptr_b! Enabling buffer!\n");
        target = malloc(sizeof(struct La_Matrix));
        la_init_matrix(target, ptr_a->rows, ptr_b->cols, ptr_a->t);
        // Allocate target on heap
    }
    else
    {
        target = ptr_result;
    }
    // tmp is used to avoid ptr_a = ptr_result or ptr_b = ptr_result

    for (int i = 0; i < ptr_a->rows; i++)
    {
        for (int j = 0; j < ptr_b->cols; j++)
        {
            for (int k = 0; k < ptr_a->cols; k++)
            {
                switch (ptr_result->t)
                {
                case LA_FLOAT_T:
                    MATIND(*target, i, j, float) += MATIND(*ptr_a, i, k, float) * MATIND(*ptr_b, k, j, float);
                    break;
                case LA_INT_T:
                    MATIND(*target, i, j, int) += MATIND(*ptr_a, i, k, int) * MATIND(*ptr_b, k, j, int);
                    break;
                default:
                    break;
                }
            }
        }
    }
    if (enable_buffer)
    {
        la_matrix_copy(target, ptr_result);
        la_destroy_matrix(target);
        free(target);
        // remove target from heap
    }
    return 0;
}

int la_matrix_pow(struct La_Matrix *ptr, unsigned int pow, struct La_Matrix *ptr_result)
{
    int enable_buffer = ptr == ptr_result;
    struct La_Matrix *target;
    if (enable_buffer)
    {
        printf("la_matrix_pow: ptr_result's address is identical to that of ptr! Enabling Buffer\n");
        target = malloc(sizeof(struct La_Matrix));
        la_init_matrix(target, ptr->rows, ptr->cols, ptr->t);
    }
    else
    {
        target = ptr_result;
    }
    if (la_matrix_copy(ptr, target) == -1)
        return -1;

    unsigned int i = pow;
    while ((i = i >> 1))
    {
        la_matrix_mul(target, target, target);
    }
    if (pow & 1)
    {
        la_matrix_mul(ptr, target, target);
    }
    if (enable_buffer)
    {
        la_matrix_copy(target, ptr_result);
        la_destroy_matrix(target);
        free(target);
    }

    return 0;
}