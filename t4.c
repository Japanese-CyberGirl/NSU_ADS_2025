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

//

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

    void front_endeque(Deque *d , int a) {
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

        d->size -=1;

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

    void hex_to_binary(char input, char* output) {
        int hex_digit;
        hex_digit = (input > 57) ? input - 'A' + 10 : input - '0'; // перевели в десятичную

        for (int i = 0; i < 4; i++) {
            output[3 - i] = (hex_digit % 2) ? '1' : '0'; // преобразуем в символ '0' или '1'
            hex_digit /= 2;
        }
        output[4] = '\0'; // добавляем завершающий нулевой символ
    }

    int main()
    {
        FILE *input = fopen("input.txt", "r");

        int N = 0;
        int M = 0;
        

        fscanf(input, "%d %d\n", &N, &M);

        Deque *left_deck = create(2 * N + 1);
        Deque *right_deck = create(2 * N + 1);

        for (int i = 1 ; i < N + 1 ; i ++ ) {
            back_endeque(left_deck, i);
            back_endeque(right_deck, -i);
        }

        for (int i = 0 ; i < M ; i ++ ) {
            char value;
            fscanf(input, "%c", &value);
            char token[5];
            int card = 0;
            hex_to_binary(value, token);

            if (token[0] == '1' && !empty(right_deck)) {
                card = (token[1] == '1') ? back_dedeque(right_deck) : front_dedeque(right_deck);
            }
            if (token[0] == '0' && !empty(left_deck)) {
                card = (token[1] == '1') ? back_dedeque(left_deck) : front_dedeque(left_deck);
            }

            if (card == 0) {
                continue;
            }

            if (token[2] == '1') {
                (token[3] == '1') ? back_endeque(right_deck, card) : front_endeque(right_deck, card);
            }
            if (token[2] == '0') {
                (token[3] == '1') ? back_endeque(left_deck, card) : front_endeque(left_deck, card);
            }
        }


        int left_size = left_deck->size;
        int right_size = right_deck->size;

        printf("%d ", left_deck->size);
        for (int i = 0 ; i < left_size ; i ++ ) {
            printf("%d ", front_dedeque(left_deck));
        }
        printf("\n");
        printf("%d ", right_deck->size);
        for (int i = 0 ; i < right_size ; i ++ ) {
            printf("%d ", front_dedeque(right_deck));
        }


        fclose(input);
        return 0;
    }