#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front, rear, size;
    int capacity;
    int* array;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int is_column_empty(int **matrix, int N, int col, int *processed) {
    for (int i = 0; i < N; i++) {
        if (matrix[i][col] != 0 || processed[col] == 1) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *input = fopen("input.txt", "r");

    int N, M;
    fscanf(input, "%d %d", &N, &M);

    int **matrix = (int**)calloc(N, sizeof(int*));
    int *processed = (int*)calloc(N, sizeof(int));
    
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        int inp, out;
        fscanf(input, "%d %d", &inp, &out);
        matrix[inp-1][out-1] = 1;
    }
    fclose(input);

    Queue* queue = createQueue(N);
    int *topological_array = (int*)calloc(N, sizeof(int));
    int cnt = 0;

    for (int i = 0; i < N; i++) {
        if (is_column_empty(matrix, N, i, processed)) {
            enqueue(queue, i);
            processed[i] = 1;
        }
    }

    while (!isEmpty(queue)) {
        int u = dequeue(queue);
        topological_array[cnt++] = u + 1;

  
        for (int j = 0; j < N; j++) {
            matrix[u][j] = 0;
        }


        for (int v = 0; v < N; v++) {
            if (!processed[v] && is_column_empty(matrix, N, v, processed)) {
                enqueue(queue, v);
                processed[v] = 1;
            }
        }
    }

    if (cnt != N) {
        printf("bad course\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d ", topological_array[i]);
        }
        printf("\n");
    }


    return 0;
}