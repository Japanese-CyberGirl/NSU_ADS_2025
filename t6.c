#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value;
    struct node *left;
    struct node *right;
} tree;

tree *add(char c) {
    tree *t = (tree*)calloc(1, sizeof(tree));
    t->value = c;
    t->left = NULL;
    t->right = NULL;
    return t;
}

tree *create_tree(FILE *input) {
    char token;
    fscanf(input, "%c", &token);
    tree *root = add(token);

    if (token == '+' || token == '-' || token == '*' || token == '/') {
        root->left = create_tree(input);
        root->right = create_tree(input);
    }
    return root;
}

int evaluate(tree *t) {
    if (t == NULL) {return 0;}

    //если узел лист - значит это число
    if (t->left == NULL && t->right == NULL) {
        return t->value - '0';
    }

    int leftvalue = evaluate(t->left);
    int rightvalue = evaluate(t->right);

    if (t->value == '+') {
        return leftvalue + rightvalue;
    }
    if (t->value == '-') {
        return leftvalue - rightvalue;
    }
    if (t->value == '*') {
        return leftvalue * rightvalue;
    }
    if (t->value == '/') {
        if (rightvalue == 0) {
            printf("NO\n");
            exit(0);
        }
        return leftvalue / rightvalue;
    }

}

int main() {
    FILE *input = fopen("input.txt", "r");

    tree *root = create_tree(input);
    fclose(input);

    printf("%d\n", evaluate(root));

    return 0;
}