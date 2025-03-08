#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool containsCharacter(const char *str, char ch) {
    return strchr(str, ch) != NULL;
}

struct list {
    char data;
    int value;
    struct list *next;
};

typedef struct Stack {
    struct list *top;
} Stack;

int empty(Stack *S) {
    return (S->top == NULL);
}

int top_value(Stack *S) {
    return(S->top->value);
}

char top_char(Stack *S) {
    return(S->top->data);
}

void create_stack(Stack **S) {
    *S = (Stack *)calloc(1, sizeof(Stack));
    (*S)->top = NULL;
}

char pop(Stack *S) {
    char a; 
    struct list *p;
    p = S->top;
    a = p->data;
    S->top = p->next;
    free(p);
    return a;
}

void push(Stack *S, char a) {
    struct list *p;
    p = (struct list*)calloc(1, sizeof(struct list));
    p->data = a;
    if (containsCharacter("*/", a)) {
        p->value = 2;
    } else if (containsCharacter("+-", a)) {
        p->value = 1;
    } else {
        p->value = 0;
    }
    p->next = S->top;
    S->top = p;
}

int main()
{
    FILE* input = fopen("input.txt", "r");

    char *string = (char*)calloc(1000, sizeof(char)); 
    fscanf(input, "%s", string);

    Stack *stack;
    create_stack(&stack);
    
    int len = strlen(string);
    char token;

    for (int i = 0 ; i < len ; i ++ ) {

        token = string[i];

        if (!containsCharacter("()*/+-", token)) {
            printf("%c", token);
        }

        if (token == '(') {
            push(stack, token);
        }

        if (token == ')') {
            while (!empty(stack) && top_char(stack) != '(') {
                printf("%c", pop(stack));
            }
            if (!empty(stack) && top_char(stack) == '(') {
                pop(stack);
            }
        }

        if (containsCharacter("*/", token)) {
            while (!empty(stack) && top_value(stack) >= 2) {
                printf("%c", pop(stack));
            }
            push(stack, token);
        }

        if (containsCharacter("+-", token)) {
            while (!empty(stack) && top_value(stack) >= 1) {
                printf("%c", pop(stack));
            }
            push(stack, token);
         }

    }

    while (!empty(stack)) {
        printf("%c", pop(stack));
    }

    fclose(input);
    free(string);
    return 0;
}