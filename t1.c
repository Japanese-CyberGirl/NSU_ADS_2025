#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue_item {
    int where;
    int from_where;
} Queue_item;

typedef struct Queue {
    int size;
    int first;
    int leng;
    Queue_item *arr;
} Queue;

Queue *create() {
    Queue *q = (Queue*)calloc(1, sizeof(Queue));
    q->first = 0;
    q->leng = 0;
    q->size = 1;
    q->arr = (Queue_item*)calloc(q->size, sizeof(Queue_item));
    return q;
}

int empty(Queue *q) {
    return (q->leng == 0);
}

void enqueue(Queue *q, int where, int from_where) {
    if (q->leng == q->size) {
        q->arr = (Queue_item*)realloc(q->arr, sizeof(Queue_item) * q->size * 2);
        if (q->first > 0) {
            memcpy(q->arr + q->size, q->arr, (q->first) * sizeof(Queue_item));
        }
        q->size *= 2;
    }
    int pos = (q->first + q->leng) % q->size;
    q->arr[pos].where = where;
    q->arr[pos].from_where = from_where;
    q->leng ++ ;
}

Queue_item dequeue(Queue *q) {
    Queue_item a = q->arr[q->first];
    q->first = (q->first + 1) % q->size;
    q->leng--;
    return a;
}



int main()
{
    FILE *input = fopen("input.txt", "r");

    Queue *queue = create();


    int N = 0;
    int M = 0;
    fscanf(input, "%d %d", &N, &M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0 ; i < N ; i ++ )  {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }


    for (int i = 0 ; i < M ; i ++ ) {
        int inp;
        int out;
        fscanf(input, "%d %d", &inp, &out);
        matrix[inp-1][out-1] = 1;
    }

    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++ ) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0 ; i < N ; i ++ ) {
        for (int j = 0 ; j < N ; j ++) {
            if (matrix[i][j] == 1) {
                break;
            }
        }
        enqueue(queue, )
    }

    fclose(input);
    return 0;
}