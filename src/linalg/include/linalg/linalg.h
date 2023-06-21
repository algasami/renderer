// Linalg.h

#ifndef LINALG_H
#define LINALG_H

#include <stddef.h>

struct La_Mat_2d
{
    size_t rows, cols;
    void *buffer;
};

struct La_Mat_2d *const la_init_mat_2d(size_t rows, size_t cols, size_t size);
void la_destroy_mat_2d(struct La_Mat_2d *ptr);

#endif
