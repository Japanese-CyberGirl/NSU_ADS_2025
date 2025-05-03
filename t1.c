#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertex_count;
    struct Node **adjacent;
} Graph;

struct Node *create_Node(int vertex) {
    struct Node *new_Node = (struct Node*)calloc(1, sizeof(struct Node));
    new_Node->vertex = vertex;
    new_Node->next = NULL;
    return new_Node;
} 

struct Graph *create_Graph(int num_of_vertices) {
    struct Graph *graph = (struct Graph*)malloc(sizeof(Graph));  
    graph->vertex_count = num_of_vertices;
    graph->adjacent = (struct Node**)calloc(num_of_vertices + 1, sizeof(Node*));

    for (int i = 0 ; i < num_of_vertices ; i ++ ) {
        graph->adjacent[i] = NULL;
    }
    return graph;
}

void add_Edge(struct Graph *graph, int source, int destination) {
    struct Node *new_Node = create_Node(destination);
    new_Node->next = graph->adjacent[source];
    graph->adjacent[source] = new_Node;
}

void print_graph(struct Graph *graph) {
    for (int v = 0; v < graph->vertex_count ; v ++ ) {
        struct Node *temp = graph->adjacent[v];
        printf("Vertex %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void BFS(Graph *graph, int start_vertex, int *distances) {
    bool *visited = (bool*)calloc(graph->vertex_count, sizeof(bool));
    int *queue = (int*)calloc(graph->vertex_count, sizeof(int));
    int front = 0;
    int rear = 0;

    for (int i = 0 ; i < graph->vertex_count ; i ++ ) {
        distances[i] = -1;
    }
    
    visited[start_vertex] = true;
    distances[start_vertex] = 0;
    queue[rear++] = start_vertex;

    while (front < rear) {
        int current = queue[front++];
        Node *temp = graph->adjacent[current];

        while (temp) {
            int neighboor = temp->vertex;
            if (!visited[neighboor]) {
                visited[neighboor] = true;
                distances[neighboor] = distances[current] + 1;
                queue[rear++] = neighboor;  
            }
            temp = temp->next;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int N = 0;
    int M = 0;

    fscanf(stdin, "%d %d", &N, &M);

    Graph *graph = create_Graph(N);  

    for (int i = 0 ; i < M ; i ++ ) {
        int v = 0;
        int u = 0;
        fscanf(stdin, "%d %d", &v, &u);
        add_Edge(graph, v - 1, u - 1);
    }

    int *distances = (int*)calloc(N, sizeof(int));
    BFS(graph, 0, distances);

    for (int i = 0 ; i < N ; i ++ ) {
        printf("%d\n", distances[i]);
    }

    return 0;
}
