#include <stdio.h>
#include <stdlib.h>

#define SIZE 100001

typedef struct Conn {
    int dest;
    struct Conn* next;
} Conn;

Conn* links[SIZE];
int checked[SIZE], entry_time[SIZE], min_reach[SIZE], prev_node[SIZE], marks[SIZE];
int clock = 0;

void link_nodes(int a, int b) {
    Conn* c1 = (Conn*)malloc(sizeof(Conn));
    c1->dest = b;
    c1->next = links[a];
    links[a] = c1;

    Conn* c2 = (Conn*)malloc(sizeof(Conn));
    c2->dest = a;
    c2->next = links[b];
    links[b] = c2;
}

void explore(int node) {
    checked[node] = 1;
    entry_time[node] = min_reach[node] = ++clock;
    int kids = 0;

    Conn* curr = links[node];
    while(curr) {
        int neighbor = curr->dest;
        
        if(neighbor == prev_node[node]) {
            curr = curr->next;
            continue;
        }

        if(!checked[neighbor]) {
            prev_node[neighbor] = node;
            kids++;
            explore(neighbor);
            
            if(min_reach[node] > min_reach[neighbor])
                min_reach[node] = min_reach[neighbor];
            
            if(prev_node[node] != -1 && min_reach[neighbor] >= entry_time[node])
                marks[node] = 1;
        } else {
            if(min_reach[node] > entry_time[neighbor])
                min_reach[node] = entry_time[neighbor];
        }
        curr = curr->next;
    }

    if(prev_node[node] == -1 && kids > 1)
        marks[node] = 1;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int n, m, a, b;
    fscanf(input, "%d %d", &n, &m);

    for(int i = 1; i <= n; i++) {
        links[i] = NULL;
        prev_node[i] = -1;
    }

    for(int i = 0; i < m; i++) {
        fscanf(input, "%d %d", &a, &b);
        if(a != b) link_nodes(a, b);
    }

    for(int i = 1; i <= n; i++) {
        if(!checked[i]) explore(i);
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(marks[i]) cnt++;
    }

    printf("%d\n", cnt);
    for(int i = 1; i <= n; i++) {
        if(marks[i]) printf("%d ", i);
    }

    fclose(input);
    return 0;
}