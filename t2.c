#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int u, v;
    int used;
} Edge;

int n, e;
Edge *edges;
int **adj;
int *adj_count;
int *degree;
int *visited;

int *path;
int path_index;

void add_edge(int u, int v, int idx) {
    edges[idx].u = u;
    edges[idx].v = v;
    edges[idx].used = 0;
    adj[u][adj_count[u]++] = idx;
    adj[v][adj_count[v]++] = idx;
    degree[u]++;
    degree[v]++;
}

void DFS(int u) {
    visited[u] = 1;
    for (int i = 0; i < adj_count[u]; ++i) {
        int edge_idx = adj[u][i];
        Edge edge = edges[edge_idx];
        int v = (edge.u == u) ? edge.v : edge.u;
        if (!visited[v]) {
            DFS(v);
        }
    }
}

int is_connected() {
    int start = -1;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return 0;
    
    memset(visited, 0, (n + 1) * sizeof(int));
    DFS(start);
    
    for (int i = 1; i <= n; ++i) {
        if (degree[i] > 0 && !visited[i]) {
            return 0;
        }
    }
    return 1;
}

void find_euler_path(int u) {
    for (int i = 0; i < adj_count[u]; ++i) {
        int edge_idx = adj[u][i];
        if (!edges[edge_idx].used) {
            edges[edge_idx].used = 1;
            int v = (edges[edge_idx].u == u) ? edges[edge_idx].v : edges[edge_idx].u;
            find_euler_path(v);
            path[path_index++] = edge_idx + 1;
        }
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");

    fscanf(input, "%d %d", &n, &e);
    
    edges = (Edge*)calloc(e, sizeof(Edge));
    
    adj = (int**)calloc(n + 1, sizeof(int*));
    for (int i = 1; i <= n; ++i) {
        adj[i] = (int*)calloc(e, sizeof(int));
    }
    adj_count = (int*)calloc(n + 1, sizeof(int));
    degree = (int*)calloc(n + 1, sizeof(int));
    visited = (int*)calloc(n + 1, sizeof(int));
    path = (int*)calloc(e, sizeof(int));
    path_index = 0;
    
    for (int i = 0; i < e; ++i) {
        int u, v;
        fscanf(input, "%d %d", &u, &v);
        add_edge(u, v, i);
    }
    fclose(input);
    
    if (!is_connected()) {
        printf("NO\n");
        return 0;
    }
    
    int odd_degree = 0;
    int start = 1;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] % 2) {
            odd_degree++;
            start = i;
        }
    }
    
    if (odd_degree != 0 && odd_degree != 2) {
        printf("NO\n");
        return 0;
    }
    
    find_euler_path(start);
    
    if (path_index != e) {
        printf("NO\n");
        return 0;
    }
    
    printf("YES\n");
    for (int i = path_index - 1; i >= 0; --i) {
        printf("%d\n", path[i]);
    }
    
    
    return 0;
}