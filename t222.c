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

void decrement(int **matrix, int *massive, int N, int x) {
    for (int i = 0 ; i < N ; i ++ ) {
        massive[i] -= (matrix[x][i] == 1) ? 1 : 0;
        matrix[x][i] -= (matrix[x][i] == 1) ? 1 : 0;
    }
}

int zero_column(int *massive, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        if (massive[i] == 0 ) {
            return i;
        }
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
        massive[out-1] += 1;
    }

    print_matrix(matrix, N);
    printf("\n");
    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", massive[i]);
    }

    int *topological_array = (int*)calloc(N, sizeof(int));

    int counter = 0 ;
    int i = 0 ;

    for (int i = 0 ; i < N ; i ++ ) {
        int temp = zero_column(massive, N);
        if (temp == -1) {
            printf("bad course\n");
            return 0;
        }
        topological_array[i] = temp + 1;
        decrement(matrix, massive, N, temp);
    }

    printf("\n");

    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", topological_array[i]);
    }


    fclose(input);
    return 0;
}