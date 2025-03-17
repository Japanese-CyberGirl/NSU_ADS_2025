#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
} Tree;


int main()
{

    FILE *input = fopen("input.bin", "rb");
    FILE *output = fopen("output.bin", "wb");

    int N = 0;

    fread(&N, sizeof(int), 1, input);



    return 0;
}