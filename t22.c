#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int main() {
    FILE *file = fopen("input.txt", "r");

    int n, m;
    fscanf(file, "%d %d", &n, &m);
    

    int matrix[MAX_N][MAX_N] = {0};
    int in_degree[MAX_N] = {0};


    for (int k = 0; k < m; k++) {
        int i, j;
        fscanf(file, "%d %d", &i, &j);
        matrix[i-1][j-1] = 1;
        in_degree[j-1]++;
    }
    fclose(file);

    int result[MAX_N];
    int pos = 0;
    

    int queue[MAX_N];
    int front = 0, rear = 0;


    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        result[pos++] = u + 1; 
        
        for (int v = 0; v < n; v++) {
            if (matrix[u][v]) {
                if (--in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (pos != n) {
        printf("bad course\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    return 0;
}