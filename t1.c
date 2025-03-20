#include <stdio.h>
#include <stdlib.h>

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
    return new;
}

void left_rotation(Node *root, Node *x) {
    Node *y = x->right; // y - правый потомок х
    x->right = y->left; // левый потомок превращается в правого потомка x
    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    }
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

int main()
{

    FILE *input = fopen("input.bin", "rb");
    FILE *output = fopen("output.bin", "wb");

    int N = 0;

    fread(&N, sizeof(int), 1, input);



    return 0;
}