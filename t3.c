#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key; 
    char color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int counter; 
} Node;

Node *creation(int key) { 
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

void insert(Node **root, int key, FILE *output) { 
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
            fprintf(output, "dupe\n");
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
    fprintf(output, "added\n");
}

Node *treeMinimum(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void transplant(Node **root, Node *u, Node *v) {
    if (u->parent == NULL) {
        *root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void deleteFixup(Node **root, Node *x) {
    while (x != *root && x->color == 'B') {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                left_rotation(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == 'B') && (w->right == NULL || w->right->color == 'B')) {
                w->color = 'R';
                x = x->parent;
            }
            else {
                if (w->right == NULL || w->right->color == 'B') {
                    w->left->color = 'B';
                    w->color = 'R';
                    right_rotation(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (w->right != NULL) {
                    w->right->color = 'B';
                }
                left_rotation(root, x->parent);
                x = *root;
            }
        }
        else {
            Node *w = x->parent->left;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                right_rotation(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == 'B') && (w->left == NULL || w->left->color == 'B')) {
                w->color = 'R';
                x = x->parent;
            }
            else {
                if (w->left == NULL || w->left->color == 'B') {
                    w->right->color = 'B';
                    w->color = 'R';
                    left_rotation(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (w->left != NULL) {
                    w->left->color = 'B';
                }
                right_rotation(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = 'B'; 
}

void removeNode(Node **root, int key, FILE *output) {
    Node *z = NULL;
    Node *current = *root;
    while(current != NULL && current->key != key) {
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if (current == NULL) {
        fprintf(output, "miss\n");
        return;
    }
    z = current;
    fprintf(output, "removed\n");
    char y_original_color = z->color;
    Node *x;
    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        Node *y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(root, y , y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == 'B') {
        deleteFixup(root, x);
    }
}

Node *lowerBound(Node *root, int key) {
    Node *current = root;
    Node *result = NULL;
    while (current != NULL) {
        if (current->key >= key) {
            result = current;
            current = current->left;   
        }
        else {
            current = current->right;
        }
    }
    return result;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");



    Node *root = NULL;

    char string[52];
    char command[10];
    int value = 0;

    int M = 0;
    fscanf(input, "%d", &M);
    fgetc(input); 

    for (int i = 0; i < M; i++) {
        if (fgets(string, sizeof(string), input) == NULL) {
            break;
        }
        if (sscanf(string, "%s %d", command, &value) < 1) {
            continue; 
        }
        if (strcmp(command, "add") == 0) {
            insert(&root, value, output);
        }
        else if (strcmp(command, "remove") == 0) {
            removeNode(&root, value, output);
        }
        else if (strcmp(command, "lower") == 0) {
            Node *result = lowerBound(root, value);
            if (result != NULL) {
                fprintf(output, "%d\n", result->key);
            }
            else {
                fprintf(output, "###\n");
            }
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}