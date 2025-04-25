#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int main()
{

    FILE *input = fopen("input.txt", "r");

    int N = 0; //vertex_counter;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);
    printf("%d %d\n", N, M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < N ; i ++ )  {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0 ; i < M ; i ++ ) {
        int x_cor = 0;
        int y_cor = 0;
        fscanf(input, "%d %d", &x_cor, &y_cor);
        matrix[x_cor - 1][y_cor - 1] = 1;
        matrix[y_cor - 1][x_cor - 1] = 1;
    }

    printf("\n");

    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");



    fclose(input);
    return 0;
}