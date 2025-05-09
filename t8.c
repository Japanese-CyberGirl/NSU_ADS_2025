#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

typedef struct Link {
    int dest;
    int num;
    struct Link* next;
} Link;

Link* graph[MAX];
int seen[MAX], entry[MAX], low[MAX];
int step = 0;
int answer[MAX] = {0};

void add_edge(int a, int b, int id) {
  
    Link* new1 = (Link*)calloc(1, sizeof(Link));
    new1->dest = b;
    new1->num = id;
    new1->next = graph[a];
    graph[a] = new1;

    Link* new2 = (Link*)calloc(1, sizeof(Link));
    new2->dest = a;
    new2->num = id;
    new2->next = graph[b];
    graph[b] = new2;
}

void find_bridges(int v, int prev_id) {
    seen[v] = 1;
    entry[v] = low[v] = ++step;

    Link* curr = graph[v];
    while(curr != NULL) {
        int u = curr->dest;
        int edge_id = curr->num;

        if(edge_id == prev_id) {
            curr = curr->next;
            continue;
        }

        if(seen[u]) {
            if(low[v] > entry[u]) {
                low[v] = entry[u];
            }
        } else {
            find_bridges(u, edge_id);
            if(low[v] > low[u]) {
                low[v] = low[u];
            }
            if(low[u] > entry[v]) {
                answer[edge_id] = 1;
            }
        }
        curr = curr->next;
    }
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int n, m, a, b;
    fscanf(input, "%d %d", &n, &m);


    for(int i = 1; i <= n; i++) {
        graph[i] = NULL;
        seen[i] = 0;
    }


    for(int i = 1; i <= m; i++) {
        fscanf(input, "%d %d", &a, &b);
        if(a != b) { 
            add_edge(a, b, i);
        }
    }


    for(int i = 1; i <= n; i++) {
        if(!seen[i]) {
            find_bridges(i, -1);
        }
    }


    int count = 0;
    for(int i = 1; i <= m; i++) {
        if(answer[i]) count++;
    }

    printf("%d\n", count);
    for(int i = 1; i <= m; i++) {
        if(answer[i]) {
            printf("%d ", i);
        }
    }

    fclose(input);
    return 0;
}