#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 3001
#define MAX_HEAP_SIZE 1000000

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct HeapElement {
    int distance;
    int node;
} HeapElement;

Edge *graph[MAX_N];

void pushHeap(HeapElement *heap, int *heapSize, HeapElement elem) {
    int i = (*heapSize)++;
    while (i > 0) {
        int parent = (i - 1)/2;
        if (heap[parent].distance <= elem.distance) break;
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i] = elem;
}

HeapElement popHeap(HeapElement *heap, int *heapSize) {
    HeapElement result = heap[0];
    HeapElement last = heap[--(*heapSize)];
    int i = 0;
    while (i*2 + 1 < *heapSize) {
        int left = i*2 +1;
        int right = i*2 +2;
        int minChild = (right < *heapSize && heap[right].distance < heap[left].distance) ? right : left;
        if (last.distance <= heap[minChild].distance) break;
        heap[i] = heap[minChild];
        i = minChild;
    }
    heap[i] = last;
    return result;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file\n");
        return 1;
    }

    int N, M, K;
    if (fscanf(input, "%d %d %d", &N, &M, &K) != 3) {
        printf("Invalid input format\n");
        fclose(input);
        return 1;
    }

    int (*queries)[2] = malloc(K * sizeof(int[2]));
    for (int i = 0; i < K; i++) {
        if (fscanf(input, "%d %d", &queries[i][0], &queries[i][1]) != 2) {
            printf("Invalid query format\n");
            free(queries);
            fclose(input);
            return 1;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        if (fscanf(input, "%d %d %d", &u, &v, &w) != 3) {
            printf("Invalid edge format\n");
            free(queries);
            fclose(input);
            return 1;
        }
        Edge *edge = (Edge*)malloc(sizeof(Edge));
        edge->to = v;
        edge->weight = w;
        edge->next = graph[u];
        graph[u] = edge;

        edge = (Edge*)malloc(sizeof(Edge));
        edge->to = u;
        edge->weight = w;
        edge->next = graph[v];
        graph[v] = edge;
    }

    for (int q = 0; q < K; q++) {
        int S = queries[q][0];
        int T = queries[q][1];

        int dist[MAX_N];
        int prev[MAX_N];
        for (int i = 1; i <= N; i++) {
            dist[i] = INT_MAX;
            prev[i] = -1;
        }
        dist[S] = 0;

        HeapElement heap[MAX_HEAP_SIZE];
        int heapSize = 0;
        pushHeap(heap, &heapSize, (HeapElement){0, S});

        while (heapSize > 0) {
            HeapElement elem = popHeap(heap, &heapSize);
            int u = elem.node;
            if (u == T) break; // Оптимизация: ранний выход
            if (elem.distance > dist[u]) continue;

            for (Edge *edge = graph[u]; edge; edge = edge->next) {
                int v = edge->to;
                int new_dist = dist[u] + edge->weight;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    prev[v] = u;
                    pushHeap(heap, &heapSize, (HeapElement){new_dist, v});
                }
            }
        }

        if (dist[T] == INT_MAX) {
            printf("NO\n");
        } else {
            int path[MAX_N];
            int current = T;
            int path_len = 0;
            while (current != S) {
                if (current == -1) { // На случай некорректных данных
                    path_len = -1;
                    break;
                }
                path[path_len++] = current;
                current = prev[current];
            }
            if (path_len == -1) {
                printf("NO\n");
                continue;
            }
            path[path_len++] = S;

            // Реверс массива
            for (int i = 0; i < path_len/2; i++) {
                int tmp = path[i];
                path[i] = path[path_len-1-i];
                path[path_len-1-i] = tmp;
            }

            printf("YES %d %d", dist[T], path_len);
            for (int i = 0; i < path_len; i++) {
                printf(" %d", path[i]);
            }
            printf("\n");
        }
    }

    // Освобождение памяти
    for (int i = 1; i <= N; i++) {
        Edge *edge = graph[i];
        while (edge) {
            Edge *temp = edge;
            edge = edge->next;
            free(temp);
        }
        graph[i] = NULL;
    }
    free(queries);
    fclose(input);

    return 0;
}