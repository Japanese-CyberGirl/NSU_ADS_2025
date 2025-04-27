#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void DFS(int y, int x, int **matrix, bool **visited, int N) {
    if (x < 0 || x >= N || y < 0 || y >= N) return;
    if (matrix[y][x] == 1 || visited[y][x]) return;

    visited[y][x] = true;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        DFS(y + dy[i], x + dx[i], matrix, visited, N);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");

    int N;
    fscanf(input, "%d", &N);
    fgetc(input); 

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    bool **visited = (bool**)calloc(N, sizeof(bool*));
    for (int i = 0; i < N; i++) {
        visited[i] = (bool*)calloc(N, sizeof(bool));
    }

    int entrance_x = -1, entrance_y = 0;

    for (int i = 0; i < N; i++) {
        int j = 0;
        while (j < N) {
            char temp = fgetc(input);
            if (temp == '\n' || temp == '\r') continue; 
            if (temp == '*') {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
                entrance_x = (i == 0 && entrance_x == -1 && temp == ' ') ? j : entrance_x;
            }
            j++;
        }
    }
    fclose(input);

    if (entrance_x != -1 && entrance_y != -1) {
        DFS(entrance_y, entrance_x, matrix, visited, N);
    }

    int counter = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 0 && !visited[i][j]) {
                counter++;
                DFS(i, j, matrix, visited, N);
            }
        }
    }

    printf("%d\n", counter);

    return 0;
}
