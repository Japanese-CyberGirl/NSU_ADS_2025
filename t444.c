#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Deque {
    int size;
    int front;
    int back;
    int capacity;
    int *arr;
} Deque;

Deque *create(int capacity) {
    Deque *d = (Deque*)calloc(1, sizeof(Deque));
    d->front = 0;
    d->back = 0;
    d->size = 0;
    d->capacity = capacity;
    d->arr = (int*)calloc(d->capacity, sizeof(int));
    return d;
}

int empty(Deque *d) {
    return (d->size == 0);
}

void front_endeque(Deque *d, int a) {
    if (d->size == d->capacity) {
        int new_capacity = d->capacity * 2;
        int *new_arr = (int*)calloc(new_capacity, sizeof(int));

        int first_part = d->capacity - d->front;
        memcpy(new_arr, d->arr + d->front, first_part * sizeof(int));
        memcpy(new_arr + first_part, d->arr, d->front * sizeof(int));

        free(d->arr);
        d->arr = new_arr;

        d->front = 0;
        d->back = d->size;
        d->capacity = new_capacity;
    }

    d->front = (d->front - 1 + d->capacity) % d->capacity;
    d->arr[d->front] = a;
    d->size += 1;
}

void back_endeque(Deque *d, int a) {
    if (d->size == d->capacity) {
        int new_capacity = d->capacity * 2;
        int *new_arr = (int*)calloc(new_capacity, sizeof(int));

        int first_part = d->capacity - d->front;
        memcpy(new_arr, d->arr + d->front, first_part * sizeof(int));
        memcpy(new_arr + first_part, d->arr, d->front * sizeof(int));

        free(d->arr);
        d->arr = new_arr;

        d->front = 0;
        d->back = d->size;
        d->capacity = new_capacity;
    }

    d->arr[d->back] = a;
    d->back = (d->back + 1) % d->capacity;
    d->size += 1;
}

int front_dedeque(Deque *d) {
    if (empty(d)) {
        return -1;
    }

    int value = d->arr[d->front];
    d->front = (d->front + 1) % d->capacity;
    d->size -= 1;
    return value;
}

int back_dedeque(Deque *d) {
    if (empty(d)) {
        return -1;
    }

    d->back = (d->back - 1 + d->capacity) % d->capacity;
    int value = d->arr[d->back];
    d->size -= 1;
    return value;
}

int front(Deque *d) {
    if (empty(d)) return -1;
    return d->arr[d->front];
}

int back(Deque *d) {
    if (empty(d)) return -1;
    return d->arr[(d->back - 1 + d->capacity) % d->capacity];
}

void free_deque(Deque *d) {
    free(d->arr);
    free(d);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    int N;
    fscanf(input, "%d", &N);
    int *array = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        fscanf(input, "%d", &array[i]);
    }
    char commands[400001];
    fscanf(input, "%s", commands);
    fclose(input);

    Deque *d = create(N);
    int L = 0, R = 0;
    int len = strlen(commands);

    for (int i = 0; i < len; i++) {
        if (commands[i] == 'R') {
            // Добавляем новый элемент в окно
            while (!empty(d) && array[R] > array[back(d)]) {
                back_dedeque(d);
            }
            back_endeque(d, R);
            R++;
        } else if (commands[i] == 'L') {
            // Удаляем элемент из окна
            if (front(d) == L) {
                front_dedeque(d);
            }
            L++;
        }
        // Выводим максимум в текущем окне
        printf("%d\n", array[front(d)]);
    }

    free_deque(d);
    free(array);
    return 0;
}