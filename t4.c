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
    int largest = i;  
    int l = Left(i);
    int r = Right(i);

    if (l < h->value && h->heap[l] > h->heap[largest]) {  
        largest = l;
    }

    if (r < h->value && h->heap[r] > h->heap[largest]) {  
        largest = r;
    }

    if (largest != i) {
        int temp = h->heap[i];
        h->heap[i] = h->heap[largest];
        h->heap[largest] = temp;

        heapifyDown(h, largest);
    }
}

void heapifyUp(Heap *h, int i) {
    while (i != 0 && h->heap[Parent(i)] < h->heap[i]) { 
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

int peek(Heap *h) {
    return h->heap[0];
}

typedef struct box {
    int *keys;
    int *counts;
    int size;
} box;

void create_box(box *box, int capacity) {
    box->keys = (int*)calloc(capacity, sizeof(int));
    box->counts = (int*)calloc(capacity, sizeof(int));
    box->size = 0;
}

void mark_box(box *box, int key) {
    for (int i = 0 ; i < box->size ; i ++ ) {
        if (box->keys[i] == key) {
            box->counts[i] ++ ;
            return ;
        }
    }
    box->keys[box->size] = key;
    box->counts[box->size] = 1;
    box->size ++ ;
}

int isremoved(box *box, int key) {
    for (int i = 0 ; i < box->size ; i ++ ) {
        if (box->keys[i] == key && box->counts[i] > 0 ) {
            return 1;
        }
    }
    return 0;
}

void cleanheap(Heap *h, box *box) {
    while (h->value > 0 && isremoved(box, peek(h))) {
        int key = pop(h);
        for (int i = 0 ; i < box->size ; i ++ ) {
            if (box->keys[i] == key) {
                box->counts[i] -- ;
                break;
            }
        }
    }
}


int main()
{
    FILE *input = fopen("input.txt", "r");

    int N = 0;
    fscanf(input, "%d", &N);

    int *array = (int*)calloc(N, sizeof(int));
    for (int i = 0 ; i < N ; i ++ ) {
        fscanf(input, "%d", &array[i]);
    }

    char commands[400001];
    fscanf(input, "%s", commands);

    Heap *heap = create(N);
    box box;
    create_box(&box, N);

    int L = 0 ;
    int R = 0 ;

    int i = 0;
    while(commands[i] != '\0') {
        if (commands[i] == 'R') {
            push(heap, array[R]);
            R ++ ;
        } 
        else if (commands[i] == 'L') {
            mark_box(&box, array[L]) ;
                L ++ ;
        }
        cleanheap(heap, &box);
        printf("%d\n", peek(heap));
    }


    fclose(input);
    return 0;
}