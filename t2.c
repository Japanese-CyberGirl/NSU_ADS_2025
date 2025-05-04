#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertex_count;
    struct Node **adjacent;
} Graph;

Node *create_Node(int vertex) {
    Node *new_Node = (Node*)calloc(1, sizeof(Node));
    new_Node->vertex = vertex;
    new_Node->next = NULL;
    return new_Node;
}

Graph *create_Graph(int num_of_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->vertex_count = num_of_vertices;
    graph->adjacent = (Node**)calloc(num_of_vertices, sizeof(Node*));
    return graph;
}

void add_Edge(Graph *graph, int source, int destination) {
    Node *new_Node = create_Node(destination);
    new_Node->next = graph->adjacent[source];
    graph->adjacent[source] = new_Node;
}

void BFS(Graph *graph, int start_vertex, int *distances) {
    bool *visited = (bool*)calloc(graph->vertex_count, sizeof(bool));
    int *queue = (int*)calloc(graph->vertex_count, sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < graph->vertex_count; i++) {
        distances[i] = -1;
    }

    visited[start_vertex] = true;
    distances[start_vertex] = 0;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int current = queue[front++];
        Node *temp = graph->adjacent[current];
        while (temp) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[current] + 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}

int main() {
    int M = 0, N = 0;
    FILE *input = fopen("input.txt", "r");

    fscanf(input, "%d %d", &M, &N);
    fgetc(input); 


    char **matrix = (char**)calloc(N, sizeof(char*));
    for (int i = 0; i < M; i++) {
        matrix[i] = (char*)calloc(N + 2, sizeof(char)); 
        fgets(matrix[i], N + 2, input);
        size_t len = strlen(matrix[i]);
        if (len > 0 && matrix[i][len - 1] == '\n') {
            matrix[i][len - 1] = '\0';
        }
 
        while (strlen(matrix[i]) < (size_t)N) {
            matrix[i][strlen(matrix[i])] = ' ';
        }
    }
    fclose(input);

    Graph *graph = create_Graph(M * N);
    int start = -1, end = -1;

    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            char ch = matrix[i][j];
            if (ch == 'X') continue;

            int current_index = i * N + j;
            if (ch == 'S') start = current_index;
            if (ch == 'F') end = current_index;

            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 0 && ni < M && nj >= 0 && nj < N && matrix[ni][nj] != 'X') {
                    int neighbor_index = ni * N + nj;
                    add_Edge(graph, current_index, neighbor_index);
                    add_Edge(graph, neighbor_index, current_index); 
                }
            }
        }
    }

    if (start == -1 || end == -1) {
        printf("-1\n");
        return 0;
    }

    if (start == end) {
        printf("0\n");
        return 0;
    }

    int *distances = (int*)calloc(M * N, sizeof(int));
    BFS(graph, start, distances);
    printf("%d\n", distances[end]);

    return 0;
}
