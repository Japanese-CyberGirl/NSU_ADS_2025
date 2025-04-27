#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_matrix(int **matrix, int N) {
    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DFS(int v , int *visited, int **matrix, int N, int component_id) {
    visited[v] = component_id;
    for (int i = 0 ; i < N ; i ++ ) {
        if (matrix[v][i] && !visited[i]) {
            DFS(i, visited, matrix, N, component_id);
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
    for (int i = 0 ; i < N ; i ++ ) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    for (int i = 0 ; i < M ; i ++ ) {
        int temp1 = 0;
        int temp2 = 0;
        fscanf(input, "%d %d", &temp1, &temp2);
        matrix[temp1-1][temp2-1] = 1;
        matrix[temp2-1][temp1-1] = 1;
    }

    fclose(input);

    
    int *visited = (int*)calloc(N, sizeof(int));

    int components = 0;
    int component_id = 0;


    for (int i = 0 ; i < N ; i ++ ) {
        if(!visited[i]) {
            component_id += 1;
            components += 1;
            DFS(i, visited, matrix, N, component_id);
        }
    }

    printf("%d\n", components);
    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", visited[i]);
    }


    return 0;
}