#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Heap {
    int *heap;
    int value;  
    int capacity;
} Heap;

Heap *create(int capacity) {
    Heap *h = (Heap*)calloc(1, sizeof(Heap));
    h->heap = (int*)calloc(capacity, sizeof(int)); ///эта типа массив крч
    h->value = 0;  
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

    if (l < h->value && h->heap[l] < h->heap[smallest]) {  
        smallest = l;
    }

    if (r < h->value && h->heap[r] < h->heap[smallest]) { 
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
    h->heap[h->value] = key;  
    h->value++;               
    heapifyUp(h, h->value - 1);  
}

int pop(Heap *h) {
    
    if (h->value == 0) {
        return 1000000;
    }

    int root = h->heap[0];
    h->heap[0] = h->heap[h->value - 1];  
    h->value--;                          
    heapifyDown(h, 0);
    return root;
}

void printHeap(Heap *h) {
    if (h->value == 0) {
        printf("Heap is empty\n");
    }
    for (int i = 0 ; i < h->value ; i ++ ) {
        printf("%d ", h->heap[i]);
    }

}

void heapsort(int *arr, int n) {

    Heap *h = create(n);

    for (int i = 0 ; i < n ; i ++ ) {
        push(h, arr[i]);
    }

    for (int i = 0 ; i < n ; i ++ ) {
        arr[i] = pop(h);
    }

}

int main()
{
    FILE *input = fopen("input.txt", "r");

    int N = 0;
    fscanf(input, "%d", &N);

    Heap *heap = create(N);
    for (int i = 0 ; i < N ; i ++ ) {
        int value = 0;
        fscanf(input, "%d", &value);
        push(heap, value);
    }

    printHeap(heap);

    fclose(input);
    return 0;
}