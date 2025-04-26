#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

void add_edge(Node **adj_list, int u, int v) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = v;
    new_node->next = adj_list[u];
    adj_list[u] = new_node;
}

void DFS(int v, int *visited, Node **adj_list, int component_id) {
    visited[v] = component_id;
    Node *current = adj_list[v];
    while (current != NULL) {
        int neighbor = current->vertex;
        if (!visited[neighbor]) {
            DFS(neighbor, visited, adj_list, component_id);
        }
        current = current->next;
    }
}

int main() {   
    FILE *input = fopen("input.txt", "r");

    int N = 0, M = 0;
    fscanf(input, "%d %d", &N, &M);

    Node **adj_list = (Node**)calloc(N, sizeof(Node*)); 
    for (int i = 0; i < N; i++) {
        adj_list[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int temp1 = 0, temp2 = 0;
        fscanf(input, "%d %d", &temp1, &temp2);
        temp1--; temp2--; 
        add_edge(adj_list, temp1, temp2);
        add_edge(adj_list, temp2, temp1); 
    }

    fclose(input);

    int *visited = (int*)calloc(N, sizeof(int));

    int components = 0;
    int component_id = 0;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            component_id += 1;
            components += 1;
            DFS(i, visited, adj_list, component_id);
        }
    }

    printf("%d\n", components);
    for (int i = 0; i < N; i++) {
        printf("%d ", visited[i]);
    }
    printf("\n");

    return 0;
}
