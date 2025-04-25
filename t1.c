#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void finding(int *array, int n, int size) {
    for (int i = 0 ; i < size; i ++ ) {
        if (array[i] == n) {
            array[i] = -1;
        }
    }
}

int summa(int *array, int size) {
    int summ = 0;
    for (int i = 0 ; i < size ; i ++ ) {
        summ += array[i];
    }
    return summ;
}

void DFS(int v , bool *visited, int **matrix, int N, int *druids, int druids_counter) {
    visited[v] = true;
    finding(druids, v + 1, druids_counter);
    for (int i = 0 ; i < N ; i ++ ) {
        if (matrix[v][i] && !visited[i]) {
            DFS(i, visited, matrix, N, druids, druids_counter);
        }
    }
}



int main()
{

    FILE *input = fopen("input.txt", "r");

    int N = 0; //vertex_counter;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < N ; i ++ )  {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    bool *visited = (bool*)calloc(N, sizeof(bool));

    for (int i = 0 ; i < M ; i ++ ) {
        int x_cor = 0;
        int y_cor = 0;
        fscanf(input, "%d %d", &x_cor, &y_cor);
        matrix[x_cor - 1][y_cor - 1] = 1;
        matrix[y_cor - 1][x_cor - 1] = 1;
    }

    int druids_counter = 0;
    fscanf(input, "%d", &druids_counter);
    int *druids = (int*)calloc(druids_counter, sizeof(int));
    
    for (int i = 0 ; i < druids_counter ; i ++ ) {
        fscanf(input, "%d", &druids[i]);
    }

    fclose(input);

    DFS(0, visited, matrix, N, druids, druids_counter);

    (summa(druids, druids_counter) == (druids_counter * (-1))) ? printf("YES\n") : printf("NO\n");

    return 0;
}