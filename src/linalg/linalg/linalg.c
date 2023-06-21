#include <linalg/linalg.h>
#include <stdlib.h>

struct La_Mat_2d *const init(size_t rows, size_t cols, size_t size)
{
    struct La_Mat_2d *const ptr = malloc(sizeof(*ptr));

    ptr->buffer = malloc(rows * cols * size);

    return ptr;
}

void la_destroy_mat_2d(struct La_Mat_2d *ptr)
{
    free(ptr->buffer);
    free(ptr);
}
