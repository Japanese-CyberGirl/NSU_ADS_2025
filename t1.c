#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void search(int v , bool *visited , int **matrix, int vertex_counter) {
    visited[v] = true;
    printf("%d \n", v);

    for (int i = 0 ; i < vertex_counter ; i ++ ) {
        if (matrix[v][i] && !visited[i]) {
            search(i , visited , matrix, vertex_counter);
        }
    }
}

void DFS(int **matrix , int vertex_counter , int start_vertex) {
    bool *visited = (bool*)calloc(vertex_counter, sizeof(bool));

    search(start_vertex, visited, matrix, vertex_counter);
}

int main()
{

    FILE *input = fopen("input.txt", "r");

    int N = 0; //vertex_counter;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);
    printf("%d %d\n", N, M);

    

    fclose(input);
    return 0;
}