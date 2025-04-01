#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//есть строка, слова разделены пробелами, вывести на экран все слова, которые не содержат тех же символов, что есть в первом слове.

int main()
{
    FILE *input = fopen("input.txt", "r");

    char *string = (char*)calloc(1000000, sizeof(char));

    while(fscanf(input, "%s", string) == 1) {
        printf("%s\n", string);
    }

    fclose(input);
    return 0;
}