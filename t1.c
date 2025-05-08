#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node** adj;
int* visited;
int* onStack;
int* path;
int pathTop = -1;
int cycleFound = 0;
int* cycle;
int cycleSize = 0;

void push(int vertex) {
    path[++pathTop] = vertex;
}

void pop() {
    pathTop--;
}

void addEdge(int u, int v) {
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void DFS(int start, int n) {
    int* stack = (int*)calloc(n, sizeof(int));
    int stackSize = 0;
    int* indexStack = (int*)calloc(n, sizeof(int));
    int indexStackSize = 0;

    stack[stackSize++] = start;
    visited[start] = 1;
    push(start);
    onStack[start] = 1;

    while (stackSize > 0 && !cycleFound) {
        int u = stack[stackSize - 1];
        Node* node = adj[u];
        int found = 0;

        while (node != NULL) {
            int v = node->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                stack[stackSize++] = v;
                push(v);
                onStack[v] = 1;
                found = 1;
                break;
            } else if (onStack[v]) {
                cycleSize = 0;
                int idx = pathTop;
                while (path[idx] != v) idx--;
                cycleSize = pathTop - idx + 1;
                cycle = (int*)calloc(cycleSize, sizeof(int));
                for (int i = idx; i <= pathTop; i++) {
                    cycle[i - idx] = path[i];
                }
                cycleFound = 1;
                return;
            }
            node = node->next;
        }

        if (!found) {
            stackSize--;
            pop();
            onStack[u] = 0;
        }
    }

    free(stack);
    free(indexStack);
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int n, m;
    fscanf(input, "%d %d", &n, &m);

    adj = (Node**)calloc(n + 1, sizeof(Node*));
    visited = (int*)calloc(n + 1, sizeof(int));
    onStack = (int*)calloc(n + 1, sizeof(int));
    path = (int*)calloc((n + 1), sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v;
        fscanf(input, "%d %d", &u, &v);
        addEdge(u, v);
    }

    for (int u = 1; u <= n && !cycleFound; u++) {
        if (!visited[u]) {
            DFS(u, n);
        }
    }

    if (cycleFound) {
        printf("%d\n", cycleSize);
        for (int i = 0; i < cycleSize; i++) {
            printf("%d ", cycle[i]);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }

    fclose(input);
    for (int i = 1; i <= n; i++) {
        Node* node = adj[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(adj);
    free(visited);
    free(onStack);
    free(path);
    if (cycleFound) free(cycle);

    return 0;
}