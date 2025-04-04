#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int priority;
    int size;
    struct Node* left;
    struct Node* right;
} Node;

int compute_priority(int key, int idx) {
    return (key * 31 + idx) % 1000007;
}

Node* create_node(int key, int idx) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = compute_priority(key, idx);
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

void update_size(Node* node) {
    if (!node) return;
    node->size = 1;
    if (node->left) node->size += node->left->size;
    if (node->right) node->size += node->right->size;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

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
    if (!root) {
        *left = *right = NULL;
        return;
    }

    if (root->key <= key) {
        *left = root;
        split(root->right, key, &root->right, right);
    } else {
        *right = root;
        split(root->left, key, left, &root->left);
    }
    update_size(root);
}

Node* insert(Node* root, Node* node) {
    if (!root) return node;

    if (node->priority > root->priority) {
        split(root, node->key, &node->left, &node->right);
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

int count_less_or_equal(Node* root, int key) {
    if (!root) return 0;

    if (root->key <= key) {
        int left_size = root->left ? root->left->size : 0;
        return left_size + 1 + count_less_or_equal(root->right, key);
    }
    return count_less_or_equal(root->left, key);
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int N, M;
    fscanf(input, "%d %d", &N, &M);

    int* arr = (int*)malloc(N * sizeof(int));
    Node* root = NULL;

    // Чтение массива и построение дерева
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &arr[i]);
        root = insert(root, create_node(arr[i], i));
    }

    // Обработка запросов
    for (int i = 0; i < M; i++) {
        int index, new_key;
        fscanf(input, "%d %d", &index, &new_key);
        index--; // Переход к 0-based индексации

        // Удаляем старый ключ
        root = remove_key(root, arr[index]);
        
        // Обновляем массив
        arr[index] = new_key;
        
        // Вставляем новый ключ
        root = insert(root, create_node(new_key, N + i)); // Уникальный "индекс"

        printf("%d\n", count_less_or_equal(root, new_key));
    }

    fclose(input);
    free(arr);
    return 0;
}