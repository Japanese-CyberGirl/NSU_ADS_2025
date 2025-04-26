#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

void add(Node **list, int u, int v) {
    Node *new = (Node*)calloc(1, sizeof(Node));
    new->vertex = v;
    new->next = list[u];
    list[u] = new;
}

void DFS(int v, int *visited, Node **list, int component_id) {
    visited[v] = component_id;
    Node *current = list[v];
    while (current != NULL) {
        int neighbor = current->vertex;
        if (!visited[neighbor]) {
            DFS(neighbor, visited, list, component_id);

        }
        current = current->next;

    }
}

int main()
{
    FILE *input = fopen("input.txt", "r");

    int N = 0; 
    int M = 0;
    fscanf(input, "%d %d", &N, &M);

    Node **list = (Node**)calloc(N, sizeof(Node*));
    for (int i = 0 ; i < N ; i ++ ) {
        list[i] = NULL;
    }

    for (int i = 0 ; i < M ; i ++ ) {
        int temp1 = 0; 
        int temp2 = 0;
        fscanf(input, "%d %d", &temp1, &temp2);
        add(list, temp1-1, temp2-1);
        add(list, temp2-1, temp1-1);
    }

    fclose(input);

    int *visited = (int*)calloc(N, sizeof(int));

    int components = 0;
    int component_id = 0;

    for (int i = 0 ; i < N ; i ++ ) {
        if (!visited[i]) {
            component_id += 1;
            components += 1;
            DFS(i, visited, list, component_id);
        }
    }

    printf("%d\n", components);
    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\t", visited[i]);
    }

    return 0;
}