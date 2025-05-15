#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 2000000000

typedef struct Edge {
    int b;
    int w;
    struct Edge *next;
} Edge;

Edge *adj[5001];
int dist[5001];
int prev[5001];
bool in_queue[5001];
int queue[10002];
int front, rear;

void add_edge(int a, int b, int w) {
    Edge *e = (Edge*)malloc(sizeof(Edge));
    e->b = b;
    e->w = w;
    e->next = adj[a];
    adj[a] = e;
}

void spfa(int start, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev[i] = -1;
        in_queue[i] = false;
    }
    dist[start] = 0;
    front = rear = 0;
    queue[rear++] = start;
    in_queue[start] = true;

    while (front != rear) {
        int u = queue[front++];
        if (front >= 10002) front = 0;
        in_queue[u] = false;

        for (Edge *e = adj[u]; e != NULL; e = e->next) {
            int v = e->b;
            int w = e->w;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    if (rear >= 10002) rear = 0;
                    in_queue[v] = true;
                }
            }
        }
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    int N, M, K;
    fscanf(input, "%d %d %d", &N, &M, &K);
    int friends[51];
    for (int i = 0; i < K; i++) {
        fscanf(input, "%d", &friends[i]);
    }

    for (int i = 0; i < M; i++) {
        int a, b, w;
        fscanf(input, "%d %d %d", &a, &b, &w);
        add_edge(a, b, w);
    }
    fclose(input);

    spfa(1, N);

    for (int i = 0; i < K; i++) {
        int v = friends[i];
        int path[5001], path_len = 0;
        int current = v;

        while (current != 1) {
            path[path_len++] = current;
            current = prev[current];
        }
        path[path_len++] = 1;

        int left = 0, right = path_len - 1;
        while (left < right) {
            int temp = path[left];
            path[left] = path[right];
            path[right] = temp;
            left++;
            right--;
        }

        printf("%d %d ", dist[v], path_len);
        for (int j = 0; j < path_len; j++) {
            printf("%d", path[j]);
            if (j != path_len - 1) printf(" ");
        }
        printf("\n");
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