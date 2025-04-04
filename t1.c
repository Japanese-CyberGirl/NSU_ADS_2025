#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int key, int priority) {
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->priority = priority;
    node->left = node->right = NULL;
    return node;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    
    if (left->priority < right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    
    if (root->key < key) {
        split(root->right, key, &root->right, right);
        *left = root;
    } else {
        split(root->left, key, left, &root->left);
        *right = root;
    }
}

Node* insert(Node* root, int key, int priority) {
    Node* new_node = create_node(key, priority);
    Node *left, *right;
    split(root, key, &left, &right);
    return merge(merge(left, new_node), right);
}

void print_parents(Node* node, int parent, int* output) {
    if (!node) return;
    
    output[node->key] = parent;
    print_parents(node->left, node->key, output);
    print_parents(node->right, -node->key, output);
}

int main() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    
    int N;
    fscanf(fin, "%d", &N);
    
    Node* root = NULL;
    for (int i = 0; i < N; i++) {
        int key, priority;
        fscanf(fin, "%d %d", &key, &priority);
        root = insert(root, key, priority);
    }
    
    int* output = calloc(N + 1, sizeof(int));
    print_parents(root, 0, output);
    
    for (int i = 1; i <= N; i++) {
        fprintf(fout, i > 1 ? " %d" : "%d", output[i]);
    }
    
    free(output);
    fclose(fin);
    fclose(fout);
    return 0;
}