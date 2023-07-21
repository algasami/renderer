#include <linalg/linalg.h>
#include <stdio.h>

int main()
{
    printf("Checking vitals of linalg.a...\n");
    printf("La_Matrix loaded\n");
    struct La_Matrix mat_a;

    la_id_matrix(&mat_a, 3, LA_INT_T);
    MATIND(mat_a, 1, 1, int) = 2;
    MATIND(mat_a, 2, 2, int) = 3;
    la_print_matrix(&mat_a);
    la_matrix_pow(&mat_a, 3, &mat_a);

    la_print_matrix(&mat_a);

    return 0;
}
