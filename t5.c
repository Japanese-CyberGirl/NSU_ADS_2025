#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *string, char *token) {
    int len1 = strlen(string);
    int len2 = strlen(token);

    int len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < len; i++) {
        if (string[i] > token[i]) {
            return 1;
        }
        if (string[i] < token[i]) {
            return -1;
        }
    }

    if (len1 < len2) {
        return -1;
    }
    if (len1 > len2) {
        return 1;
    }

    return 0;
}


typedef struct node {
    char *value;
    struct node *left;
    struct node *right;
} tree;

tree *add(tree *t, char *s) {
    if (t == NULL) {
        t = (tree*)calloc(1, sizeof(tree));
        t->value = (char*)calloc(101, sizeof(char));
        strcpy(t->value, s); 
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    if (compare(t->value, s) == 1) {
        t->left = add(t->left, s);
    }
    else if (compare(t->value, s) == -1) {
        t->right = add(t->right, s);
    }
    return t;
}

void infix(tree *t) {
    if (t == NULL) {
        return;
    }
    infix(t->left);
    printf("%s\n", t->value);
    infix(t->right);
}

int main() {
    FILE *input = fopen("input.txt", "r");

    tree *root = NULL;
    char token[101]; 
    while (fscanf(input, "%s", token) == 1) {
        root = add(root, token);
    }

    infix(root); 
    fclose(input);
    return 0;
}