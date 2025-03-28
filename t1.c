#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    Node *left;
    Node *right;
} Node;

Node *create(int key, int priority) {
    Node *new = (Node*)calloc(1, sizeof(Node));
    new->key = key;
    new->priority = priority;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void split(Node *root, int key, Node **left, Node **right) {
    if (root == NULL) {
        *left = NULL;
        *right = NULL;
        return;
    }
    if (root->key <= key) {
        split(root->right, key, &(root->right), right);
        *left = root;
    }
    else {
        split(root->left, key, &(root->left), left);
        *right = root;
    }
}

Node *merge(Node *left, Node *right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

Node *insert(Node *root, int key, int priority) {
    Node *new = create(key, priority);
    Node *left = NULL;
    Node *right = NULL;
    split(root, key, &left, &right);

    return merge(merge(left, new), right);
}

void printtree(Node *root) {
    if (root == NULL) {return;}
    printtree(root->left);
    printf("%d %d\n", root->key, root->priority);
    printtree(root->right);
}


int main()
{
    
    return 0;

}