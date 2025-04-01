#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool containsAnyChar(const char* str, const char* substr) {
    if (!str || !substr) return false;
    for (int i = 0; substr[i]; i++) {
        if (strchr(str, substr[i]))  
            return true;
    }
    return false;
}

int main() {
    FILE *input = fopen("input.txt", "r");

    char *string = (char*)calloc(1000000, sizeof(char));
    fgets(string, 1000000, input);

    fclose(input);

    char *firstWord = strtok(string, " \n");

    char *word = strtok(NULL, " \n");
    while (word) {
        //printf("%s\n", word);
        if (!containsAnyChar(firstWord, word)) printf("%s\n", word);
        word = strtok(NULL, " \n");
    }

    free(string);
    return 0;
}