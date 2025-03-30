#include <stdio.h>
#include <stdlib.h>

#define table_size 1000003 //размеры нашей хеш-таблицы

//структура для узла в цепочке для метода цепочек
struct Node {
    int key;
    struct Node *next;
} Node;

struct Hashtable {
    struct Node *table[table_size];
};

unsigned int hash (int key) {
    return (unsigned int)key % table_size;
}

void create_hash_table(struct Hashtable *ht) {
    for (int i = 0 ; i < table_size ; i ++ ) {
        ht->table[i] = NULL;
    }
}

int add(struct Hashtable *ht, int key, int *result, int *size) {
    unsigned int index = hash(key); // индекс в хеш-таблице
    struct Node *current = ht->table[index]; // добавляем элемент в хеш таблицу

    while (current != NULL) {
        if (current->key == key) {
            return 0;
        }
        current = current->next;
    }

    struct Node *new = (struct Node*)calloc(1, sizeof(struct Node));
    new->key = key;
    new->next = ht->table[index];
    ht->table[index] = new;

    result[*size] = key;
    (*size)++;

}


int main()
{
    //FILE *input = fopen("1.in", "rb");
    FILE *input = fopen("input.bin", "rb");
    int n = 0;
    fread(&n, sizeof(int), 1, input);

    int *array = (int*)calloc(n, sizeof(int));
    fread(array, sizeof(int), n , input);
    fclose(input);

    struct Hashtable ht;
    create_hash_table(&ht);

    int *result = (int*)calloc(n, sizeof(int));
    int unique = 0;

    for (int i = 0 ; i < n ; i ++ ) {
        add(&ht, array[i], result, &unique);
    }

    FILE *output = fopen("output.bin", "wb");
    fwrite(&unique, sizeof(int), 1, output);

    fwrite(result, sizeof(int), unique, output);
    fclose(output);

    free(array);
    free(result);


    return 0;
}