#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    int index;
    struct Node* left;
    struct Node* right;
    struct Node *parent;
} Node;

Node* create_node(int key, int priority, int index) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = priority;
    node->index = index;
    node->left = node->right = NULL;
    node->parent = NULL;
    return node;
}

Node* build_treap(Node** nodes, int n) {
    Node* root = nodes[0];
    Node* last = root;
    
    for (int i = 1; i < n; i++) {
        Node* current = nodes[i];
        
     
        while (last != NULL && current->priority < last->priority) {
            last = last->parent;
        }
        
        if (last == NULL) {
           
            current->left = root;
            root->parent = current;
            root = current;
        } else {
            
            current->left = last->right;
            if (last->right != NULL) {
                last->right->parent = current;
            }
            last->right = current;
            current->parent = last;
        }
        
        last = current;
    }
    
    return root;
}

void build_parent_array(Node* root, int* parent_array) {
    if (root == NULL) return;

    if (root->left) {
        parent_array[root->left->index - 1] = root->index;
        build_parent_array(root->left, parent_array);
    }

    if (root->right) {
        parent_array[root->right->index - 1] = -root->index;
        build_parent_array(root->right, parent_array);
    }
}

int compare_nodes(const void* a, const void* b) {
    Node* node_a = *(Node**)a;
    Node* node_b = *(Node**)b;
    return (node_a->key > node_b->key) - (node_a->key < node_b->key);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    int N;
    fscanf(input, "%d", &N);

    Node** nodes = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++) {
        int key, priority;
        fscanf(input, "%d %d", &key, &priority);
        nodes[i] = create_node(key, priority, i + 1);
    }

    qsort(nodes, N, sizeof(Node*), compare_nodes);

    Node* root = build_treap(nodes, N);


    int* parent_array = (int*)calloc(N, sizeof(int));
    build_parent_array(root, parent_array);

    for (int i = 0; i < N; i++) {
        printf("%d", parent_array[i]);
        if (i < N - 1) printf(" ");
    }
    printf("\n");

    fclose(input);

    return 0;
}