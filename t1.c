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

void heapifyDown(Heap *h, int i) {
    int smallest = i;
    int l = Left(i);
    int r = Right(i);

    if (l < h->size && h->heap[l] < h->heap[smallest]) {
        smallest = l;
    }

    if (r < h->size && h->heap[r] < h->heap[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[smallest];
        h->heap[smallest] = temp;

        heapifyDown(h, smallest);
    }
}

void heapifyUp(Heap *h, int i) {
    while (i != 0 && h->heap[Parent(i)] > h->heap[i]) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[Parent(i)];
        h->heap[Parent(i)] = temp;
        i = Parent(i);
    }
}

void push(Heap *h, int key) {
    h->heap[h->size] = key;
    h->size ++;
    heapifyUp(h, h->size - 1);
}

int pop(Heap *h) {
    int root = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size --;
    heapifyDown(h, 0);
    return root;
}

int main()
{
    FILE *input = fopen("input.txt", "r");
    int Q = 0;
    fscnaf(input, "%d", &Q);
    Heap *heap = create(Q);

    for (int i = 0 ; i < Q ; i ++ ) {
        char operation[10];
        fscanf(input, "%s",&operation);
    }

    return 0;
}