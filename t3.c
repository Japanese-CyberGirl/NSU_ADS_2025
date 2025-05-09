#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 301
#define HASH 9973

typedef struct {
    char name[17];
    int friends[MAX]; // Возвращаем int для друзей
    int cnt;
    int degree;
} Person;

typedef struct HashNode {
    char key[17];
    int id;
    struct HashNode* next;
} HashNode;

Person people[MAX];
HashNode* hash_table[HASH] = {0};
int N, path[MAX];
bool visited[MAX];
bool found = false;

// Оптимизированная хеш-функция
static inline unsigned hash(const char* s) {
    unsigned h = 0;
    while (*s) h = (h << 5) + tolower(*s++);
    return h % HASH;
}

// Добавление в хеш-таблицу
void add_hash(const char* name, int id) {
    char lower[17];
    strcpy(lower, name);
    for (char* p = lower; *p; ++p) *p = tolower(*p);
    
    unsigned h = hash(lower);
    HashNode* node = malloc(sizeof(HashNode));
    strcpy(node->key, lower);
    node->id = id;
    node->next = hash_table[h];
    hash_table[h] = node;
}

// Поиск в хеш-таблице
static inline int find_hash(const char* name) {
    char lower[17];
    strcpy(lower, name);
    for (char* p = lower; *p; ++p) *p = tolower(*p);
    
    unsigned h = hash(lower);
    for (HashNode* node = hash_table[h]; node; node = node->next) {
        if (strcmp(node->key, lower) == 0) return node->id;
    }
    return -1;
}

// Сортировка по убыванию степени и имени
int compare(const void* a, const void* b) {
    const int x = *(const int*)a;
    const int y = *(const int*)b;
    if (people[y].degree != people[x].degree)
        return people[y].degree - people[x].degree;
    return strcmp(people[x].name, people[y].name);
}

// Оптимизированный DFS с ранним выходом
int DFS(int step, int start) {
    if (found) return 1;
    
    if (step == N) {
        // Проверяем связь последней вершины с начальной
        for (int i = 0; i < people[path[N-1]].cnt; ++i) {
            if (people[path[N-1]].friends[i] == start) {
                found = true;
                return 1;
            }
        }
        return 0;
    }

    int current = path[step-1];
    // Проверяем всех друзей в отсортированном порядке
    for (int i = 0; i < people[current].cnt; ++i) {
        int next = people[current].friends[i];
        if (!visited[next]) {
            visited[next] = true;
            path[step] = next;
            if (DFS(step+1, start)) return 1;
            visited[next] = false;
        }
    }
    return 0;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &N);

    // Первый проход: чтение имен
    for (int i = 0; i < N; ++i) {
        char name[17];
        int k;
        fscanf(input, "%16s%d", name, &k);
        strcpy(people[i].name, name);
        add_hash(name, i);
        people[i].degree = 0;
        for (int j = 0; j < k; ++j) fscanf(input, "%*s");
    }

    // Второй проход: чтение связей
    rewind(input);
    fscanf(input, "%*d");
    for (int i = 0; i < N; ++i) {
        char name[17];
        int k;
        fscanf(input, "%16s%d", name, &k);
        people[i].cnt = 0;

        for (int j = 0; j < k; ++j) {
            char friend[17];
            fscanf(input, "%16s", friend);
            int id = find_hash(friend);
            if (id >= 0) {
                people[i].friends[people[i].cnt++] = id;
                people[id].degree++;
            }
        }
        qsort(people[i].friends, people[i].cnt, sizeof(int), compare);
    }
    fclose(input);

    // Выбор стартовой вершины с максимальной степенью
    int start = 0;
    for (int i = 1; i < N; ++i) {
        if (people[i].degree > people[start].degree ||
           (people[i].degree == people[start].degree && 
            strcmp(people[i].name, people[start].name) < 0)) {
            start = i;
        }
    }

    memset(visited, 0, sizeof(visited));
    path[0] = start;
    visited[start] = true;

    DFS(1, start);

    if (found) {
        for (int i = 0; i < N; ++i) {
            printf("%s\n", people[path[i]].name);
        }
    }

    // Освобождение памяти
    for (int i = 0; i < HASH; ++i) {
        HashNode* node = hash_table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return 0;
}