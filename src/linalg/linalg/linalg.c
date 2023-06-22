#include <linalg/linalg.h>
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

void la_id_matrix(struct La_Matrix *ptr, size_t rowcols, enum LA_ELEM_TYPES t)
{
    la_init_matrix(ptr, rowcols, rowcols, t);
    for (size_t i = 0; i < rowcols; i++)
    {
        switch (t)
        {
        case LA_FLOAT_T:
            ((float *)ptr->buffer)[i * rowcols + i] = 1.0f;
            break;
        case LA_INT_T:
            ((int *)ptr->buffer)[i * rowcols + i] = 1;
            break;
        default:
            break;
        }
    }
}
