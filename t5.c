#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compare(const char *string, const char *token) {
    int len1 = strlen(string);
    int len2 = strlen(token);
    int len = (len1 < len2) ? len1 : len2; 

    for (int i = 0; i < len; i++) {
        if (string[i] > token[i]) {
            return 1;  // string больше
        }
        if (string[i] < token[i]) {
            return -1; // token больше
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


int main()
{

    FILE *input = fopen("input.txt", "r");

    printf("%d\n", compare("abd", "abc"));



    fclose(input);
    return 0;
}