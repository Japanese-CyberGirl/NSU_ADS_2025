#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char *name;
    int *contacts;
    int cnt;
    int degree;
} Student;

Student *students;
int total;
int *path;
bool *visited;

inline void str_lower(char *s) {
    for (; *s; ++s) *s = tolower(*s);
}

int cmp_contacts(const void *a, const void *b) {
    const int *ia = a, *ib = b;
    return students[*ia].degree - students[*ib].degree;
}

inline bool is_connected(int a, int b) {
    for (int i = 0; i < students[a].cnt; ++i)
        if (students[a].contacts[i] == b) return true;
    return false;
}

bool dfs(int step) {
    if (step == total)
        return is_connected(path[step-1], path[0]);
    
    const int current = path[step-1];
    int *contacts = students[current].contacts;
    const int cnt = students[current].cnt;

    // Динамическое выделение памяти для degrees
    int *degrees = malloc(cnt * sizeof(int));
    for (int i = 0; i < cnt; ++i)
        degrees[i] = students[contacts[i]].degree;

    // Сортировка контактов по степени
    for (int i = 0; i < cnt-1; ++i) {
        for (int j = i+1; j < cnt; ++j) {
            if (degrees[j] < degrees[i]) {
                int tmp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = tmp;
                
                tmp = degrees[i];
                degrees[i] = degrees[j];
                degrees[j] = tmp;
            }
        }
    }

    bool found = false;
    for (int i = 0; i < cnt; ++i) {
        const int next = contacts[i];
        if (!visited[next]) {
            visited[next] = true;
            path[step] = next;
            if (dfs(step + 1)) {
                found = true;
                break;
            }
            visited[next] = false;
        }
    }
    
    free(degrees);
    return found;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    if (fscanf(fp, "%d", &total) != 1 || total <= 0) {
        fprintf(stderr, "Invalid student count\n");
        fclose(fp);
        return 1;
    }

    // Первый проход: чтение имен
    students = calloc(total, sizeof(Student));
    char **lower_names = malloc(total * sizeof(char *));
    
    for (int i = 0; i < total; ++i) {
        char name[17];
        int cnt;
        if (fscanf(fp, "%16s%d", name, &cnt) != 2) {
            fprintf(stderr, "Error reading student #%d\n", i+1);
            fclose(fp);
            return 1;
        }
        
        lower_names[i] = strdup(name);
        str_lower(lower_names[i]);
        
        students[i].name = strdup(name);
        students[i].contacts = malloc(cnt * sizeof(int));
        students[i].cnt = 0;
        students[i].degree = 0;
        
        for (int j = 0; j < cnt; ++j) fscanf(fp, "%*s");
    }

    // Второй проход: обработка контактов
    rewind(fp);
    fscanf(fp, "%*d");
    
    for (int i = 0; i < total; ++i) {
        char name[17];
        int cnt;
        fscanf(fp, "%16s%d", name, &cnt);
        
        students[i].cnt = 0;
        for (int j = 0; j < cnt; ++j) {
            char contact[17];
            fscanf(fp, "%16s", contact);
            str_lower(contact);
            
            for (int k = 0; k < total; ++k) {
                if (strcmp(contact, lower_names[k]) == 0) {
                    students[i].contacts[students[i].cnt++] = k;
                    break;
                }
            }
        }
    }
    fclose(fp);

    // Расчет степеней
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < students[i].cnt; ++j) {
            if (is_connected(students[i].contacts[j], i))
                students[i].degree++;
        }
    }

    // Инициализация поиска
    path = calloc(total, sizeof(int));
    visited = calloc(total, sizeof(bool));
    path[0] = 0;
    visited[0] = true;

    // Поиск и вывод результата
    if (dfs(1)) {
        for (int i = 0; i < total; ++i)
            printf("%s\n", students[path[i]].name);
    } else {
        printf("No solution\n");
    }

    // Освобождение памяти
    for (int i = 0; i < total; ++i) {
        free(students[i].name);
        free(students[i].contacts);
        free(lower_names[i]);
    }
    free(students);
    free(lower_names);
    free(path);
    free(visited);

    return 0;
}