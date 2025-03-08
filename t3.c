#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue {
    int size;
    int first;
    int leng;
    int *arr;
} Queue;

Queue *create() {
    Queue *q = (Queue*)calloc(1, sizeof(Queue));
    q->first = 0;
    q->leng = 0;
    q->size = 1;
    q->arr = (int*)calloc(q->size, sizeof(int));
    return q;
}

int empty(Queue *q) {
    return (q->leng == 0);
}

void enqueue(Queue *q, int a) {
    if (q->leng == q->size) {
        q->arr = (int*)realloc(q->arr, sizeof(int) * q->size * 2);
        if (q->first > 0) {
            memcpy(q->arr + q->size, q->arr, (q->first) * sizeof(int));
        }
        q->size *= 2;
    }
    q->arr[(q->first + q->leng++)%q->size] = a;
}

int dequeue(Queue *q) {
    int a = q->arr[q->first];
    q->first = (q->first + 1) % q->size;
    q->leng--;
    return a;
}


int main() {
    FILE *input = fopen("input.txt", "r");

    Queue *queue = create();

    int N = 0;
    int M = 0;

    fscanf(input, "%d %d", &N, &M);

    int value = 0;
    int flag = 0;
    int divider = 0;
    int summa = 0;
    int digit = 0;
    int memory_flag = 0;
    int empty_flag = 0;

    for (int i = 0 ; i < M ; i ++ ) {

        fscanf(input, "%d", &value);

        memory_flag = 0;
        empty_flag = 0;
        divider = 0;
        summa = 0;

        if (value > 0) {
            for (int j = 0 ; j < value ; j ++ ) {
                i += 1;
                fscanf(input, "%d", &digit);
                (queue->leng == N) ? memory_flag = 1 : enqueue(queue, digit);
            }
            if (memory_flag) {
                printf("Memory overflow\n");
            }
        }
        if (value < 0) {
            value *= -1;
            for (int j = 0 ; j < value ; j ++ ) {
                if (empty(queue)) {
                    empty_flag = 1;
                    break;
                }
                summa += dequeue(queue);
                divider += 1;
            }
            if (divider) {
                printf("%d\n", summa/divider);
            }
            if (empty_flag) {
                printf("Empty queue\n");
            }
        }
    }

    fclose(input);
    return 0;
}