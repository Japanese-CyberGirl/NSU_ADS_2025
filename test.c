#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Для int32_t

typedef struct Node {
    int32_t key; 
    char color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int32_t counter; 
} Node;

Node *creation(int32_t key) { 
    Node *new = (Node*)calloc(1, sizeof(Node));
    new->key = key;
    new->color = 'R';
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->counter = 1; 
    return new;
}

void left_rotation(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotation(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    }
    else if(x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void insertFixup(Node **root, Node *node) {
    while (node != *root && node->parent->color == 'R') {
        if (node->parent == node->parent->parent->left) {
            Node *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == 'R') {
                node->parent->color = 'B';
                uncle->color = 'B';
                node->parent->parent->color = 'R';
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotation(root, node);
                }
                node->parent->color = 'B';
                node->parent->parent->color = 'R';
                right_rotation(root, node->parent->parent);
            }
        }
        else {
            Node *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == 'R') {
                node->parent->color = 'B';
                uncle->color = 'B';
                node->parent->parent->color = 'R';
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotation(root, node);
                }
                node->parent->color = 'B';
                node->parent->parent->color = 'R';
                left_rotation(root, node->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

void insert(Node **root, int32_t key) { 
    Node *node = creation(key);
    Node *current = *root;
    Node *parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        }
        else if (key > current->key) {
            current = current->right;
        }
        else {
            current->counter++;
            free(node);
            return;
        }
    }

    node->parent = parent;
    if (parent == NULL) {
        *root = node;
    }
    else if (key < parent->key) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }
    insertFixup(root, node);
}

void inorderTraversal(Node *node, FILE *output) {
    if (node != NULL) {
        inorderTraversal(node->left, output);
        for (int32_t i = 0; i < node->counter; i++) { 
            fwrite(&node->key, sizeof(int32_t), 1, output); 
        }
        inorderTraversal(node->right, output);
    }
}

int main() {
    FILE *input = fopen("input.bin", "rb");

    FILE *output = fopen("output.bin", "wb");

    int32_t N = 0; 
    fread(&N, sizeof(int32_t), 1, input); 

    Node *root = NULL;
    for (int32_t i = 0; i < N; i++) { 
        int32_t temp = 0; 
        fread(&temp, sizeof(int32_t), 1, input);
        insert(&root, temp);
    }

    inorderTraversal(root, output);

    fclose(input);
    fclose(output);

    return 0;
}