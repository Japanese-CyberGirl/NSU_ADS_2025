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
    printf("\n");
}

void print_massive(int *massive, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", massive[i]);
    }
    printf("\n\n");
}


int zero_index(int *massive, int *selected, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        if (massive[i] == 0 && selected[i]) {
            selected[i] = 0;
            return i;
        }
    }
    return -1;
}


void decrement(int **matrix, int *massive, int N, int x) {
    for (int i = 0 ; i < N ; i ++ ) {
        massive[i] -= (matrix[x][i] == 1) ? 1 : 0;
        matrix[x][i] -= (matrix[x][i] == 1) ? 1 : 0;
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

    int *massive = (int*)calloc(N, sizeof(int));
    int *selected = (int*)calloc(N, sizeof(int));
    for (int i = 0 ; i < N ; i ++ ) {
        selected[i] = 1;
    }


    for (int i = 0 ; i < M ; i ++ ) {
        int inp;
        int out;
        fscanf(input, "%d %d", &inp, &out);
        if (matrix[inp-1][out-1] == 0) {
            matrix[inp-1][out-1] = 1;
            massive[out-1] += 1;
        }
    }

    int *topological_array = (int*)calloc(N, sizeof(int));


    for (int i = 0 ; i < N ; i ++ ) {
        int temp = zero_index(massive, selected, N);
        if (temp == -1) {
            printf("bad course\n");
            return 0;
        }

        topological_array[i] = temp + 1;
        decrement(matrix, massive, N, temp);


    }


    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", topological_array[i]);
    }

    fclose(input);
    return 0;
}