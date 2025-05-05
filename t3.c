#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int u;
    int v;
    double length;
} Edge;


int find(int *parents, int u) {
    if (parents[u] != u) {
        parents[u] = find(parents, parents[u]);
    }
    return parents[u];
}

void union_sets(int *parents, int u, int v) {
    u = find(parents, u);
    v = find(parents, v);
    if (u != v) {
        parents[v] = u;
    }
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y-b.y) * (a.y - b.y));
}

int compare_edges(const void *a, const void *b) {
    const Edge *edge_A = (Edge *)a;
    const Edge *edge_B = (Edge*)b;

    if (edge_A->length < edge_B->length) return -1;
    else if (edge_A->length > edge_B->length) return 1;
    else return 0;
}

bool is_existing_edge(int u, int v, Edge *existing_edges, int existing_count) {
    for (int i = 0 ; i < existing_count ; i ++ ) {
        if ((existing_edges[i].u == u && existing_edges[i].v == v) || 
            (existing_edges[i].u == v && existing_edges[i].v == u)) {
            return true;
        }
    }
    return false;
}

int main()
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int N = 0;
    fscanf(input, "%d", &N);
    Point *cities = (Point*)calloc(N + 1, sizeof(Point));
    Edge *edges = (Edge*)calloc(N * N / 2, sizeof(Edge)); //максимальное количество ребер в графе
    int edge_count = 0;
    int *parents = (int*)calloc(N + 1, sizeof(int));
    for (int i = 1 ; i <= N ; i ++ ) {
        fscanf(input, "%d %d", &cities[i].x, &cities[i].y);
        parents[i] = i;
    }

    int M = 0; //создаем объединения из уже соединенных
    Edge *existing_edges = NULL;
    fscanf(input, "%d", &M);
    if (M > 0) {
        existing_edges = calloc(M, sizeof(Edge));
        for (int i = 0 ; i < M ; i ++ ) {
            fscanf(input, "%d %d", &existing_edges[i].u, existing_edges[i].v);
        }
    }


    for (int i = 1 ; i <= N ; i ++ ) {
        for (int j = i + 1 ; j <= N ; j ++ ) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].length = distance(cities[i], cities[j]);
            edge_count += 1;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), compare_edges);

    for (int i = 0 ; i < edge_count ; i ++ ) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(parents, u) != find(parents, v)) {
            union_sets(parents, u, v);
            
            if (M == 0 || !is_existing_edge(u, v, existing_edges, M)) {
                fprintf(output, "%d %d\n", u , v);
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}