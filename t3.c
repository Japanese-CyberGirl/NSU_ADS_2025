#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Heap {
    int32_t *heap;
    int32_t value;  
    int32_t capacity;
} Heap;

Heap *create(int32_t capacity) {
    Heap *h = (Heap*)calloc(1, sizeof(Heap));
    h->heap = (int32_t*)calloc(capacity, sizeof(int32_t));
    h->value = 0;  
    h->capacity = capacity;
    return h;
}

int32_t Parent(int32_t i) {
    return (i-1)/2;
}

int32_t Left(int32_t i) {
    return (2 * i + 1);
}

int32_t Right(int32_t i) {
    return (2 * i + 2);
}

void heapifyDown(Heap *h, int32_t i) {
    int32_t smallest = i;
    int32_t l = Left(i);
    int32_t r = Right(i);

    if (l < h->value && h->heap[l] < h->heap[smallest]) {  
        smallest = l;
    }

    if (r < h->value && h->heap[r] < h->heap[smallest]) { 
        smallest = r;
    }

    if (smallest != i) {
        int32_t temp = h->heap[i];
        h->heap[i] = h->heap[smallest];
        h->heap[smallest] = temp;

        heapifyDown(h, smallest);
    }
}

void heapifyUp(Heap *h, int32_t i) {
    while (i != 0 && h->heap[Parent(i)] > h->heap[i]) {
        int32_t temp = h->heap[i];
        h->heap[i] = h->heap[Parent(i)];
        h->heap[Parent(i)] = temp;
        i = Parent(i);
    }
}

void push(Heap *h, int32_t key) {
    h->heap[h->value] = key;  
    h->value++;               
    heapifyUp(h, h->value - 1);  
}

int32_t pop(Heap *h) {

    int32_t root = h->heap[0];
    h->heap[0] = h->heap[h->value - 1];  
    h->value--;                          
    heapifyDown(h, 0);
    return root;
}


void heapsort(int32_t *arr, int32_t n) {
    Heap *h = create(n);

    for (int32_t i = 0; i < n; i++) {
        push(h, arr[i]);
    }

    for (int32_t i = 0; i < n; i++) {
        arr[i] = pop(h);
    }

    free(h->heap);
    free(h);
}

int main() {
    FILE *input = fopen("input.bin", "rb");

    FILE *output = fopen("output.bin", "wb");

    int32_t Q;
    fread(&Q, sizeof(int32_t), 1, input);

    int32_t *array = (int32_t*)calloc(Q, sizeof(int32_t));

    fread(array, sizeof(int32_t), Q, input);


    heapsort(array, Q);

    fwrite(array, sizeof(int32_t), Q, output);

    fclose(input);
    fclose(output);
    return 0;
}