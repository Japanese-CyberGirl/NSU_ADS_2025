#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

Edge *adj[3001];

typedef struct {
    long long dist;
    int vertex;
} HeapItem;

void dijkstra(int start, int N, long long *dist, int *prev) {
    const long long INF = 1e18;
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    HeapItem *heap = malloc(3000000 * sizeof(HeapItem));
    int heap_size = 0;

    #define swap(a, b) { HeapItem temp = a; a = b; b = temp; }

    void push(HeapItem item) {
        int i = heap_size++;
        heap[i] = item;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (heap[p].dist <= heap[i].dist) break;
            swap(heap[p], heap[i]);
            i = p;
        }
    }

    HeapItem pop() {
        HeapItem min_item = heap[0];
        heap[0] = heap[--heap_size];
        int i = 0;
        while (1) {
            int left = 2*i + 1;
            int right = 2*i + 2;
            int smallest = i;
            if (left < heap_size && heap[left].dist < heap[smallest].dist)
                smallest = left;
            if (right < heap_size && heap[right].dist < heap[smallest].dist)
                smallest = right;
            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            } else break;
        }
        return min_item;
    }

    push((HeapItem){0, start});

    while (heap_size > 0) {
        HeapItem min_item = pop();
        int u = min_item.vertex;
        long long current_dist = min_item.dist;

        if (current_dist > dist[u]) continue;

        for (Edge *e = adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            int w = e->weight;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                push((HeapItem){dist[v], v});
            }
        }
    }

    free(heap);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    int N, M, K;
    fscanf(input, "%d %d %d", &N, &M, &K);

    int queries[20][2];
    for (int i = 0; i < K; i++)
        fscanf(input, "%d %d", &queries[i][0], &queries[i][1]);

    for (int i = 1; i <= N; i++)
        adj[i] = NULL;

    for (int i = 0; i < M; i++) {
        int A, B, W;
        fscanf(input, "%d %d %d", &A, &B, &W);
        Edge *e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = B;
        e1->weight = W;
        e1->next = adj[A];
        adj[A] = e1;

        Edge *e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = A;
        e2->weight = W;
        e2->next = adj[B];
        adj[B] = e2;
    }
    fclose(input);

    for (int q = 0; q < K; q++) {
        int S = queries[q][0];
        int T = queries[q][1];

        long long *dist = (long long*)malloc((N + 1) * sizeof(long long));
        int *prev = (int*)malloc((N + 1) * sizeof(int));
        dijkstra(S, N, dist, prev);

        if (dist[T] >= 1e18) {
            printf("NO\n");
        } else {
            int path[3001], path_len = 0;
            int current = T;

            while (current != S) {
                path[path_len++] = current;
                current = prev[current];
                if (current == -1) break;
            }
            if (current == -1) {
                printf("NO\n");
            } else {
                path[path_len++] = S;

                for (int i = 0; i < path_len / 2; i++) {
                    int temp = path[i];
                    path[i] = path[path_len - 1 - i];
                    path[path_len - 1 - i] = temp;
                }

                printf("YES %lld %d", dist[T], path_len);
                for (int i = 0; i < path_len; i++)
                    printf(" %d", path[i]);
                printf("\n");
            }
        }

        free(dist);
        free(prev);
    }

    for (int i = 1; i <= N; i++) {
        Edge *e = adj[i];
        while (e != NULL) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}