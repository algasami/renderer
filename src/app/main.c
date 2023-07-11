#include <linalg/linalg.h>
#include <stdio.h>

int main()
{
    printf("Checking vitals of linalg.a...\n");
    printf("La_Matrix loaded\n");
    struct La_Matrix mat_a, mat_b;

    la_id_matrix(&mat_a, 3, LA_INT_T);
    la_init_matrix(&mat_b, mat_a.rows, mat_a.cols, mat_a.t);
    MATIND(mat_a, 1, 1, int) = 2;
    MATIND(mat_a, 2, 2, int) = 3;

    la_print_matrix(&mat_a);

    la_matrix_pow(&mat_a, 3, &mat_b);

    la_print_matrix(&mat_b);

    return 0;
}
