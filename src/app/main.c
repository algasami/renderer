#include <linalg/linalg.h>
#include <stdio.h>

int main()
{
    printf("Checking vitals of linalg.a...\n\n");
    printf("La_Matrix loaded\n\n");
    struct La_Matrix mat;
    la_id_matrix(&mat, 2, LA_INT_T);
    for (size_t i = 0; i < 2; i++)
    {
        printf("|\t");
        for (size_t j = 0; j < 2; j++)
            printf("%d\t", ((int *)mat.buffer)[i * 2 + j]);
        printf("|\n");
    }
    return 0;
}
