#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void DFS(int v, bool *visited, int **matrix, int N) {
    visited[v] = true;
    for (int i = 0; i < N; i++) {
        if (matrix[v][i] && !visited[i]) {
            DFS(i, visited, matrix, N);
        }
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    
    int N = 0;
    fscanf(input, "%d", &N);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    int a, b;
    while (fscanf(input, "%d %d", &a, &b) == 2) {
        matrix[a - 1][b - 1] = 1;
        matrix[b - 1][a - 1] = 1;
    }

    bool *visited = (bool*)calloc(N, sizeof(bool));
    int components = 0;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            DFS(i, visited, matrix, N);
            components++;
        }
    }

    printf("%d\n", components + 1);


    fclose(input);

    return 0;
}
