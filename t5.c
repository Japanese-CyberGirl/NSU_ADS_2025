#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int dest;
    struct Edge* next;
} Edge;

Edge* graph[100001];
int inDegree[100001];
int topo_order[100001];
int order_size = 0;

void linkNodes(int src, int dest) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->next = graph[src];
    graph[src] = newEdge;
}

int topologicalSort(int n) {
    int queue[100001];
    int front = 0, rear = 0;

    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int current = queue[front++];
        topo_order[order_size++] = current;

        Edge* edge = graph[current];
        while (edge != NULL) {
            int neighbor = edge->dest;
            if (--inDegree[neighbor] == 0) {
                queue[rear++] = neighbor;
            }
            edge = edge->next;
        }
    }

    return order_size == n;
}

int main() {
    int n, m;
    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        graph[i] = NULL;
        inDegree[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        fscanf(input, "%d %d", &a, &b);
        linkNodes(a, b);
        inDegree[b]++;
    }

    if (!topologicalSort(n)) {
        printf("NO\n");
        return 0;
    }

    int node_values[100001];
    for (int i = 0; i < order_size; ++i) {
        node_values[topo_order[i]] = i + 1;
    }

    printf("YES\n");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", node_values[i]);
    }
    printf("\n");

    for (int i = 1; i <= n; ++i) {
        Edge* edge = graph[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
        }
    }

    return 0;
}