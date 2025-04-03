#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value;
    struct node *left;
    struct node *right;
} tree;

tree *create_node(char c) {
    tree *node = (tree *)calloc(1, sizeof(tree));
    node->value = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void add(tree **root, char c) {
    while (*root != NULL) {
        if (c < (*root)->value) {
            root = &(*root)->left;  
        } else {
            root = &(*root)->right;  
        }
    }
    *root = create_node(c);
}

void preorder(tree *root) {
    if (root == NULL) {
        return;
    }
    printf("%c", root->value);
    preorder(root->left);
    preorder(root->right);
}


int main() {
    FILE *input = fopen("input.txt", "r");

    char lines[100][100];
    int line_count = 0;
    
    while (fscanf(input, "%s", lines[line_count]) != EOF) {
        line_count ++ ;
    }
    
    tree *root = NULL;
    
    for (int i = line_count - 1; i >= 0; i--) {
        for (int j = 0; lines[i][j] != '\0'; j++) {
            add(&root, lines[i][j]);
        }
    }
    
    preorder(root);
    
    fclose(input);
    
    return 0;
}