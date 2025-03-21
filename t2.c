#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define length 8

typedef struct box {

    char element[length];

} box;

typedef struct list {

    box* element;
    int current_size;
    int potential_size;

} list;

void create_list(list* list) {
    list->current_size = 0;
    list->potential_size = 1;
    list->element = (box*)calloc(1, sizeof(box));
}

void add_eleement(list *list, char* string) {
    list->potential_size = (list->current_size == list->potential_size) ? list->potential_size * 2 : list->potential_size;
    list->element = (box*)realloc(list->element, list->potential_size * sizeof(box));

    box* token = &list->element[list->current_size];
    strcpy(token->element, string);
    list->current_size += 1;
}

int main()
{
    FILE *input = fopen("input.txt", "r");

    int N = 0;
    fscanf(input, "%d", &N);

    list* massive = (list*)calloc(1000001, sizeof(list));
    for (int i = 0 ; i < 1000001 ; i ++ ) {
        create_list(&massive[i]);
    }

    for (int i = 0 ; i < N ; i ++ ) {
        int digit = 0;
        char token[length];
        fscanf(input, "%d %s", &digit, token);
        add_eleement(&massive[digit], token);
    }

    for (int i = 0 ; i < 1000001 ; i ++ ) {
        for (int j = 0 ; j < massive[i].current_size ; j ++ ) {
            printf("%d %s\n", i , massive[i].element[j].element);
        }
    }
    

    fclose(input);
    return 0;
}