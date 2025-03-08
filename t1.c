#include <stdio.h>
#include <stdlib.h>

#define table_size 1000003 //размеры нашей хеш-таблицы

//структура для узла в цепочке для метода цепочек
struct Node {
    int key;
    struct Node *next;
};

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




int main()
{
    return 0;
}