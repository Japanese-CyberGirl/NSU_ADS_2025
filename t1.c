#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Heap {
    int *heap;
    int size;
    int capacity;
} Heap;

Heap *create(int capacity) {
    Heap *h = (Heap*)calloc(1, sizeof(Heap));
    h->heap = (int*)calloc(capacity, sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

int Parent(int i) {
    return (i-1)/2;
}

int Left(int i) {
    return (2 * i + 1);
}

int Right(int i) {
    return (2 * i + 2);
}

void heapiDown(Heap *h, int i) {
    int largest = i;
    int l = left(i);
    int r = right(i);

    if (l < h->size && h->heap[l] > h->heap[largest]) {
        largest = l;
    }
    if (r < h->size && h->heap[r] > h->heap[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = temp;
        heapiDown(h, largest);

    }
}

