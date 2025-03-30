#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HASH_SIZE (1 << 20)
#define HASH_MASK (HASH_SIZE - 1)
#define MAX_ITERATIONS 2000000

typedef struct HashNode {
    uint64_t key;
    uint64_t value;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_SIZE] = {NULL};

uint64_t hash(uint64_t key) {
    return key & HASH_MASK;
}

void hashInsert(uint64_t key, uint64_t value) {
    uint64_t h = hash(key);
    HashNode *node = malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = hashTable[h];
    hashTable[h] = node;
}

int64_t hashFind(uint64_t key) {
    uint64_t h = hash(key);
    HashNode *node = hashTable[h];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = hashTable[i];
        while (node != NULL) {
            HashNode *next = node->next;
            free(node);
            node = next;
        }
    }
}

uint64_t func(uint64_t s, uint64_t a, uint64_t b, uint64_t c, uint64_t M) {
    return (s * s * a + s * b + c) % M;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    uint64_t M, a, b, c;
    fscanf(input, "%llu", &M);
    fscanf(input, "%llu %llu %llu", &a, &b, &c);
    fclose(input);

    uint64_t state = 1;
    uint64_t l = 0, r = 0;

    for (uint64_t i = 0; i < MAX_ITERATIONS; i++) {
        int64_t pos = hashFind(state);
        if (pos != -1) {
            l = pos;
            r = i;
            break;
        }
        hashInsert(state, i);
        state = func(state, a, b, c, M);
    }

    FILE *output = fopen("output.txt", "w");
    fprintf(output, "%llu %llu\n", l, r);
    fclose(output);

    freeHashTable();
    return 0;
}