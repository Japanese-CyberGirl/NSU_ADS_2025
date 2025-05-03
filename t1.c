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
    struct Graph *graph = (struct Graph*)calloc(num_of_vertices, sizeof(Graph));
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


int main()
{

    return 0;
}