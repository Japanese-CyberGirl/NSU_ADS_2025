#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    int index;
    int size;
    struct Node* left;
    struct Node* right;
} Node;

int compute_priority(int key, int index) {
    return (key * 31 + index) % 1000007;
}

Node* create_node(int key, int index) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = compute_priority(key, index);
    node->index = index;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

void update_size(Node* node) {
    if (node == NULL) return;
    node->size = 1;
    if (node->left) node->size += node->left->size;
    if (node->right) node->size += node->right->size;
}

Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update_size(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update_size(right);
        return right;
    }
}

void split(Node* root, int key, Node** left, Node** right) {
    if (root == NULL) {
        *left = NULL;
        *right = NULL;
        return;
    }

    if (root->key <= key) {
        *left = root;
        split(root->right, key, &(root->right), right);
        update_size(root);
    } else {
        *right = root;
        split(root->left, key, left, &(root->left));
        update_size(root);
    }
}

Node* insert(Node* root, Node* node) {
    if (root == NULL) return node;

    if (node->priority > root->priority) {
        split(root, node->key, &(node->left), &(node->right));
        update_size(node);
        return node;
    }

    if (node->key <= root->key) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    update_size(root);
    return root;
}

Node* remove_by_index(Node* root, int index) {
    if (root == NULL) return NULL;

    if (index < root->index) {
        root->left = remove_by_index(root->left, index);
    } else if (index > root->index) {
        root->right = remove_by_index(root->right, index);
    } else {
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }
    update_size(root);
    return root;
}

int count_less_or_equal(Node* root, int key) {
    if (root == NULL) return 0;

    if (root->key <= key) {
        int left_size = root->left ? root->left->size : 0;
        return left_size + 1 + count_less_or_equal(root->right, key);
    } else {
        return count_less_or_equal(root->left, key);
    }
}

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    int N, M;
    fscanf(input, "%d %d", &N, &M);

    Node* root = NULL;
    Node** nodes = (Node**)malloc((N + 1) * sizeof(Node*));

    for (int i = 1; i <= N; i++) {
        int key;
        fscanf(input, "%d", &key);
        nodes[i] = create_node(key, i);
        root = insert(root, nodes[i]);
    }

    for (int i = 0; i < M; i++) {
        int index, new_key;
        fscanf(input, "%d %d", &index, &new_key);

   
        root = remove_by_index(root, index);
        
       
        nodes[index]->key = new_key;
        nodes[index]->priority = compute_priority(new_key, index);
        nodes[index]->left = nodes[index]->right = NULL;
        nodes[index]->size = 1;
        

        root = insert(root, nodes[index]);

        fprintf(output, "%d\n", count_less_or_equal(root, new_key));
    }


    fclose(input);
    fclose(output);
    return 0;
}