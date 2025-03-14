#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 1000000

typedef struct Node {
    int value;
    struct Node* next;
} Node;

unsigned long hash(int key) {
    return ((unsigned long)key) % MAX_N;
}

int main() {
    FILE *inputFile, *outputFile;
    int n;
    inputFile = fopen("1.in", "rb");
    fread(&n, sizeof(int), 1, inputFile);
    int *A = (int *)malloc(n * sizeof(int));
    fread(A, sizeof(int), n, inputFile);
    fclose(inputFile);
    Node* hash_table[MAX_N] = {NULL}; 
    int *unik = (int *)malloc(n * sizeof(int)); 
    int k = 0; 

    for (int i = 0; i < n; ++i) {
        unsigned long index = hash(A[i]);
        Node* current = hash_table[index];
        while (current != NULL && current->value != A[i]) {
            current = current->next;
        }

        if (current == NULL) { 
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->value = A[i];
            new_node->next = hash_table[index];
            hash_table[index] = new_node;
            unik[k++] = A[i]; 
        }
    }

    outputFile = fopen("output.bin", "wb");
    fwrite(&k, sizeof(int), 1, outputFile);
    fwrite(unik, sizeof(int), k, outputFile);
    fclose(outputFile);
    free(A);
    free(unik);
    
    for (int i = 0; i < MAX_N; ++i) {
        Node* current = hash_table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
