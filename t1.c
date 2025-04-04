#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;          
    int priority;     
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;


Node* createNode(int key, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void split(Node* root, int key, Node** left, Node** right) {
    if (root == NULL) {
        *left = NULL;
        *right = NULL;
    } else if (root->key <= key) {
        split(root->right, key, &(root->right), right);
        *left = root;
        if (root->right != NULL) {
            root->right->parent = root;
        }
    } else {
        split(root->left, key, left, &(root->left));
        *right = root;
        if (root->left != NULL) {
            root->left->parent = root;
        }
    }
}

Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->right->parent = left;
        return left;
    } else {
        right->left = merge(left, right->left);
        right->left->parent = right;
        return right;
    }
}

Node* insert(Node* root, int key, int priority) {
    Node* newNode = createNode(key, priority);
    Node* left = NULL;
    Node* right = NULL;
    split(root, key, &left, &right);
    return merge(merge(left, newNode), right);
}

Node* removeNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (root->key == key) {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }

    if (key < root->key) {
        root->left = removeNode(root->left, key);
        if (root->left != NULL) {
            root->left->parent = root;
        }
    } else {
        root->right = removeNode(root->right, key);
        if (root->right != NULL) {
            root->right->parent = root;
        }
    }
    return root;
}

Node* find(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}


int main() {
    Node* root = NULL;

    // Пример использования
    root = insert(root, 5, 10);
    root = insert(root, 3, 5);
    root = insert(root, 7, 15);
    root = insert(root, 2, 3);
    root = insert(root, 4, 7);

    printf("Inorder traversal after insertion:\n");
    inorderTraversal(root);

    root = removeNode(root, 3);
    printf("\nInorder traversal after removing key 3:\n");
    inorderTraversal(root);

    Node* found = find(root, 7);
    if (found != NULL) {
        printf("\nFound node with key 7, priority: %d\n", found->priority);
    } else {
        printf("\nNode with key 7 not found\n");
    }

    freeTree(root);
    return 0;
}