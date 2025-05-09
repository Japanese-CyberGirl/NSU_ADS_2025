#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100001

typedef struct Connection {
    int target;
    struct Connection* next;
} Connection;

Connection* main_graph[MAX_NODES];
Connection* reversed_graph[MAX_NODES];
int checked[MAX_NODES];
int exit_order[MAX_NODES];
int component_id[MAX_NODES];
int order_pos = 0;
int components = 0;

void add_connection(Connection** list, int to) {
    Connection* new_link = (Connection*)malloc(sizeof(Connection));
    new_link->target = to;
    new_link->next = *list;
    *list = new_link;
}

void first_pass(int node) {
    checked[node] = 1;
    Connection* current = main_graph[node];
    while(current) {
        if(!checked[current->target]) {
            first_pass(current->target);
        }
        current = current->next;
    }
    exit_order[order_pos++] = node;
}

void second_pass(int node) {
    checked[node] = 1;
    component_id[node] = components;
    Connection* current = reversed_graph[node];
    while(current) {
        if(!checked[current->target]) {
            second_pass(current->target);
        }
        current = current->next;
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    int nodes, edges;
    fscanf(input, "%d %d", &nodes, &edges);
    

    for(int i = 1; i <= nodes; i++) {
        main_graph[i] = reversed_graph[i] = 0;
        checked[i] = component_id[i] = 0;
    }
    

    for(int i = 0; i < edges; i++) {
        int a, b;
        fscanf(input, "%d %d", &a, &b);
        add_connection(&main_graph[a], b);
        add_connection(&reversed_graph[b], a);
    }
    

    for(int i = 1; i <= nodes; i++) {
        if(!checked[i]) {
            first_pass(i);
        }
    }
    

    for(int i = 1; i <= nodes; i++) checked[i] = 0;
    
  
    for(int i = order_pos-1; i >= 0; i--) {
        int node = exit_order[i];
        if(!checked[node]) {
            components++;
            second_pass(node);
        }
    }
    

    printf("%d\n", components);
    for(int i = 1; i <= nodes; i++) {
        printf("%d ", component_id[i]);
    }
    
    return 0;
}