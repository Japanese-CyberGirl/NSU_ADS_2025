#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    int priority;
    int size;
    struct node *left;
    struct node *right;
} Node;

int getSize(Node *tree) {
    if (!tree) return 0;
    return tree->size;
}

void updateSize(Node *tree) {
    tree->size = getSize(tree->left) + getSize(tree->right) + 1;
}

Node *makeNode(int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = val;
    newNode->priority = rand();
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->size = 1;
    return newNode;
}

Node *mergeTrees(Node *leftTree, Node *rightTree) {
    if (!leftTree) return rightTree;
    if (!rightTree) return leftTree;

    if (leftTree->priority < rightTree->priority) {
        leftTree->right = mergeTrees(leftTree->right, rightTree);
        updateSize(leftTree);
        return leftTree;
    } else {
        rightTree->left = mergeTrees(leftTree, rightTree->left);
        updateSize(rightTree);
        return rightTree;
    }
}

void splitTree(Node *tree, int val, Node **leftTree, Node **rightTree) {
    if (!tree) {
        *leftTree = NULL;
        *rightTree = NULL;
        return;
    }

    if (tree->value <= val) {
        *leftTree = tree;
        splitTree(tree->right, val, &(*leftTree)->right, rightTree);
    } else {
        *rightTree = tree;
        splitTree(tree->left, val, leftTree, &(*rightTree)->left);
    }
    updateSize(tree);
}

Node *insert(Node *tree, int val) {
    Node *left = NULL, *right = NULL;
    splitTree(tree, val, &left, &right);
    Node *newNode = makeNode(val);
    Node *temp = mergeTrees(left, newNode);
    return mergeTrees(temp, right);
}

Node *removeNode(Node *tree, int val) {
    Node *left = NULL, *mid = NULL, *right = NULL;
    splitTree(tree, val - 1, &left, &mid);
    splitTree(mid, val, &mid, &right);
    if (mid) {
        Node *tmp = mid;
        mid = mergeTrees(mid->left, mid->right);
        free(tmp);
    }
    return mergeTrees(mergeTrees(left, mid), right);
}

bool hasValue(Node *tree, int val) {
    if (!tree) return false;
    if (tree->value == val) return true;

    if (tree->value < val) {
        return hasValue(tree->right, val);
    } else {
        return hasValue(tree->left, val);
    }
}

int countSmaller(Node *tree, int val) {
    if (!tree) return 0;

    if (tree->value > val) {
        return countSmaller(tree->left, val);
    } else {
        int leftSize = tree->left ? tree->left->size : 0;
        return leftSize + 1 + countSmaller(tree->right, val);
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    Node *tree = NULL;
    int n, m, num;
    int pos, newNum;

    fscanf(file, "%d %d", &n, &m);

    int *numbers = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &num);
        numbers[i] = num;
        tree = insert(tree, num);
    }

    for (int i = 0; i < m; i++) {
        fscanf(file, "%d %d", &pos, &newNum);
        pos--;
        tree = removeNode(tree, numbers[pos]);
        numbers[pos] = newNum;
        tree = insert(tree, newNum);
        printf("%d\n", countSmaller(tree, newNum));
    }

    fclose(file);
    return 0;
}