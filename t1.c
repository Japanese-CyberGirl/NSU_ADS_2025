#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *create(int value) {
    Tree *new = (Tree*)calloc(1, sizeof(Tree));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Tree *insert(Tree *tree, int value) {
    if (tree = NULL) {
        return create(value);
    }
    
    if (value <= tree->value) { //нестрогое неравенство для сохранения дубликатов
        tree->left = insert(tree->left, value);
    }
    if (value > tree->value) {
        tree->right = insert(tree->right, value);
    }

    return tree;
}

Tree *search(Tree *tree, int value) {
    if (tree == NULL || tree->value == value) {
        return tree;
    }

    if (value < tree->value) {
        return search(tree->left, value);
    }   else {
        return search(tree->left, value);
    }

}

Tree *delete(Tree *tree, int value) {
    if (tree == NULL) {
        return tree;
    }

    if (value < tree->value) {
        tree->left = delete(tree->left, value);
    } else if (value > tree->value) {
        tree->right = delete(tree->right, value);
    } else {
        //если дальше нет узлов
        if (tree->left == NULL) {
            Tree *temp = tree->right;
            return temp;
        } else if (tree->right == NULL) {
            Tree *temp = tree->left;
            return temp;
        }
    }
}




int main()
{

    FILE *input = fopen("input.bin", "rb");
    FILE *output = fopen("output.bin", "wb");

    int N = 0;

    fread(&N, sizeof(int), 1, input);



    return 0;
}