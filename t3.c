#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    freopen("input.txt", "r", stdin);
    int N = 0;
    fscanf(stdin, "%d", &N);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < N ; i ++ ) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    for (int i = 0 ; i < N ; i ++ ) {
        int j = 0;
        while (j < N) {
            char ch;
            fscanf(stdin, "%c", &ch);
            matrix[i][j] = (ch == '0' || ch == '1') ? ((i == j) ? 1 : (ch - '0')) : matrix[i][j];
            j = (ch == '0' || ch == '1') ? j + 1 : j;
        }
    }

    for (int k = 0 ; k < N ; k ++ ) {
        for (int i = 0 ; i < N ; i ++ ) {
            for (int j = 0 ; j < N ; j ++ ) {
                if (matrix[i][k] && matrix[k][j]) {
                    matrix[i][j] = 1;
                }
            }
        }
    }

    print_matrix(matrix, N);
    return 0;
}
