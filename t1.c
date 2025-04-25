#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE *input = fopen("input.txt", "r");

    int N = 0;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < M ; i ++ ) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    for (int i = 0 ; i < M ; i ++ ) {
        int i_cor = 0;
        int j_cor = 0;
        fscanf(input, "%d %d", &i_cor, &j_cor);
        matrix[i_cor][j_cor] = 1;
        matrix[j_cor][i_cor] = 1;
    }

    fclose(input);
    return 0;
}