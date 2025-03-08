#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} tree;

tree *add(tree *t , int x) {
    if (t == NULL) {
        t = (tree*)calloc(1, sizeof(tree));
        t->value = x;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    if (t->value > x) {
        t->left = add(t->left, x);
    }
    else {
        if (t->value < x) {
            t->right = add(t->right, x);
        }
    }
    return t;
}

int height(tree *t) {
    if (t == NULL) {
        return 0;
    }

    int left_height = height(t->left);
    int right_height = height(t->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}



int main()
{
    tree *root = NULL;

    FILE *input = fopen("input.txt", "r");
    int token;

    while(fscanf(input, "%d", &token) == 1) {
        root = add(root, token);
    }

    printf("%d\n", height(root) - 1);

    fclose(input);

    return 0;
}