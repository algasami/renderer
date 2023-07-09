#include <linalg/linalg.h>
#include <stdio.h>

int main()
{
    printf("Checking vitals of linalg.a...\n");
    printf("La_Matrix loaded\n");
    struct La_Matrix mat_a, mat_b, mat_r;
    la_id_matrix(&mat_a, 3, LA_INT_T);
    la_init_matrix(&mat_b, 3, 2, LA_INT_T);
    la_init_matrix(&mat_r, 3, 2, LA_INT_T);
    la_print_matrix(&mat_a);
    printf("---\n");
    la_print_matrix(&mat_b);
    la_matrix_mul(&mat_a, &mat_b, &mat_r);
    printf("---\n");
    la_print_matrix(&mat_r);

    la_destroy_matrix(&mat_a);
    la_destroy_matrix(&mat_b);
    la_destroy_matrix(&mat_r);

    return 0;
}
