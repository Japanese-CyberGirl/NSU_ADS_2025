#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(int **matrix, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int zero_column(int **matrix, int N, int *massive) {
    int temp = 1;
    for (int j = 0 ; j < N ; j ++ ) {
        for (int i = 0 ; i < N ; i ++ ) {
            if (matrix[i][j] != 0 || massive[j] == 1) {
                temp = 0;
                break;
            }
        }
        if (temp) {
            massive[j] = 1;
            return j;
        }
        temp = 1;
    }
    return -1;
}

void row_to_zero(int **matrix, int N, int x) {
    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            if (i == x) matrix[i][j] = 0;
        }
    }
}

int main()
{
    FILE *input = fopen("input.txt", "r");

    int N = 0;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < N ; i ++ )  {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    int *massive = (int*)calloc(N, sizeof(int*));


    for (int i = 0 ; i < M ; i ++ ) {
        int inp;
        int out;
        fscanf(input, "%d %d", &inp, &out);
        matrix[inp-1][out-1] = 1;
    }
    //matrix[i][j] - i строка j столбец
    int *topological_array = (int*)calloc(N, sizeof(int));

    for (int i = 0 ; i < N ; i ++ ) {
        //print_matrix(matrix, N);
        //printf("\n");
        int x = zero_column(matrix, N, massive);
        if (x == -1) {
            printf("bad course\n");
            return 0;
        }
        //printf("%d\n\n", x);
        topological_array[i] = x+1;
        row_to_zero(matrix, N, x);
    }

    ////print_matrix(matrix, N);
    //printf("\n");
    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", topological_array[i]);
    }

    fclose(input);
    return 0;
}