#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100001
#define HASH_SIZE 200003

typedef struct {
    char name[21];
    int id;
} Word;

typedef struct HashEntry {
    Word* word;
    struct HashEntry* next;
} HashEntry;

Word words[MAX];
HashEntry* hash_table[HASH_SIZE];
int word_count = 1;
int defined[MAX] = {0};

typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node* graph[MAX];
int visited[MAX];
bool found_loop = false;

unsigned int hash(char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

int get_id(char* name) {
    unsigned int h = hash(name);
    HashEntry* entry = hash_table[h];
    
    while (entry) {
        if (strcmp(entry->word->name, name) == 0)
            return entry->word->id;
        entry = entry->next;
    }
    
    Word* new_word = &words[word_count];
    strcpy(new_word->name, name);
    new_word->id = word_count;
    
    HashEntry* new_entry = malloc(sizeof(HashEntry));
    new_entry->word = new_word;
    new_entry->next = hash_table[h];
    hash_table[h] = new_entry;
    
    return word_count++;
}

void check_loop(int id) {
    visited[id] = 1;
    
    Node* curr = graph[id];
    while (curr) {
        if (visited[curr->to] == 1) {
            found_loop = true;
            return;
        }
        if (visited[curr->to] == 0) {
            check_loop(curr->to);
        }
        curr = curr->next;
    }
    visited[id] = 2;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int n;
    fscanf(input, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        char word[21];
        fscanf(input, "%s", word);
        int id = get_id(word);
        
        if (defined[id]++ > 0) {
            printf("multiple definition\n");
            return 0;
        }
        
        int k;
        fscanf(input, "%d", &k);
        for (int j = 0; j < k; j++) {
            fscanf(input, "%s", word);
            int from_id = get_id(word);
            
            Node* new_node = malloc(sizeof(Node));
            new_node->to = id;
            new_node->next = graph[from_id];
            graph[from_id] = new_node;
        }
    }
    
    for (int i = 1; i < word_count; i++) {
        if (!visited[i]) {
            check_loop(i);
            if (found_loop) {
                printf("loop detected\n");
                return 0;
            }
        }
    }
    
    printf("correct\n");
    return 0;
}