#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 750
#define MAX_EDGES ((MAXN * (MAXN - 1)) / 2)

typedef struct {
    int u, v;
    double cost;
} Edge;

typedef struct {
    int x, y;
} City;

City cities[MAXN];
Edge edges[MAX_EDGES];
Edge resultEdges[MAXN];  
int parent[MAXN];

int N = 0, M = 0;
int edgeCount = 0;
int resultCount = 0;


int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}


void unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB)
        parent[rootA] = rootB;
}


int cmpEdges(const void *a, const void *b) {
    const Edge *e1 = (const Edge *)a;
    const Edge *e2 = (const Edge *)b;
    if (e1->cost < e2->cost) return -1;
    if (e1->cost > e2->cost) return 1;
    return 0;
}


int cmpResultEdges(const void *a, const void *b) {
    const Edge *e1 = (const Edge *)a;
    const Edge *e2 = (const Edge *)b;
    if (e1->u != e2->u)
        return e1->u - e2->u;
    return e1->v - e2->v;
}


double distance(int i, int j) {
    int dx = cities[i].x - cities[j].x;
    int dy = cities[i].y - cities[j].y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    FILE *input = fopen("input.txt", "r");

    fscanf(input, "%d", &N);
    for (int i = 0; i < N; ++i) {
        fscanf(input, "%d %d", &cities[i].x, &cities[i].y);
    }

    for (int i = 0; i < N; ++i)
        parent[i] = i;

    fscanf(input, "%d", &M);
    for (int i = 0; i < M; ++i) {
        int u, v;
        fscanf(input, "%d %d", &u, &v);
        unite(u - 1, v - 1); 
    }

    edgeCount = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (find(i) != find(j)) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].cost = distance(i, j);
                edgeCount++;
            }
        }
    }

    qsort(edges, edgeCount, sizeof(Edge), cmpEdges);


    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            resultEdges[resultCount].u = u + 1;
            resultEdges[resultCount].v = v + 1;
            resultCount++;
            unite(u, v);
        }
    }

    qsort(resultEdges, resultCount, sizeof(Edge), cmpResultEdges);

    for (int i = 0; i < resultCount; ++i) {
        printf("%d %d\n", resultEdges[i].u, resultEdges[i].v);
    }

    fclose(input);
    return 0;
}