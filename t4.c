#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} tree;
//слава шарит за матан
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

int vertex(tree *t, int level) {
    if (t == NULL) {
        return 0;
    }

    if (level == 0) {
        return 1;
    }

    int leftvertex = vertex(t->left, level - 1);
    int rightvertex = vertex(t->right, level - 1);

    return leftvertex + rightvertex;

}



int main()
{
    tree *root = NULL;

    FILE *input = fopen("input.txt", "r");
    
    int level = 0;

    fscanf(input, "%d", &level);

    int token;

    while(fscanf(input, "%d", &token) == 1) {
        root = add(root, token);
    }

    printf("%d\n", vertex(root, level));

    fclose(input);

    return 0;
}