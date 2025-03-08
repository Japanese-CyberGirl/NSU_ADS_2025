#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool containsCharacter(const char *str, char ch) {
    return strchr(str, ch) != NULL;
}

struct list {
    int digit;
    struct list *next;
};

typedef struct Stack {
    struct list *top;
} Stack;

int empty(Stack *S) {
    return (S->top == NULL);
}


void create_stack(Stack **S) {
    *S = (Stack *)calloc(1, sizeof(Stack));
    (*S)->top = NULL;
}

int pop(Stack *S) {
    int a; 
    struct list *p;
    p = S->top;
    a = p->digit;
    S->top = p->next;
    free(p);
    return a;
}

void push(Stack *S, int a) {
    struct list *p;
    p = (struct list*)calloc(1, sizeof(struct list));
    p->digit = a;
    p->next = S->top;
    S->top = p;
}

int main()
{
    FILE *input = fopen("input.txt", "r");  

    char *string = (char*)calloc(2000, sizeof(char));
    fgets(string, 2000, input);

    Stack *stack;
    create_stack(&stack);

    int len = strlen(string);
    char token;
    int a = 0;
    int b = 0;
    int c = 0;

    for (int i = 0 ; i < len ; i ++ ) {
        token = string[i];

        if (isspace(token)) {
            continue;
        }

        if (isdigit(token)) {
            int degree = 0;
            while (i < len && isdigit(string[i  ])) {
                degree = degree * 10 + (string[i] - '0');
                i += 1;
                token = string[i];
            }
            i -= 1;
            push(stack, degree);
        }

        if (containsCharacter("*/+-", token)) {
            a = pop(stack);
            b = pop(stack);
            c = ('*' == token) ? b * a : c;
            c = ('/' == token) ? b / a : c;
            c = ('+' == token) ? b + a : c;
            c = ('-' == token) ? b - a : c;

            push(stack, c);
        }
    }

    while(!empty(stack)) {
        printf("%d", pop(stack));
    }

    fclose(input);
    return 0;
}
