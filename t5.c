#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Функция для поиска топологического порядка через DFS
bool dfs(int v, int **matrix, int *visited, int N, int *sort, int *index) {
    visited[v] = 1;  // Вершина помечена как "в процессе обработки"

    // Пройдем по всем соседям вершины v
    for (int i = 0; i < N; i++) {
        if (matrix[v][i] == 1) {  // Если существует ребро от v к i
            if (visited[i] == 1) {  // Если вершина уже в процессе обработки, то найден цикл
                return false;
            }
            if (visited[i] == 0) {  // Если вершина еще не посещена
                if (!dfs(i, matrix, visited, N, sort, index)) {
                    return false;
                }
            }
        }
    }

    visited[v] = 2;  // Вершина обработана
    sort[(*index)++] = v;  // Добавляем вершину в топологический порядок
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);

    int N = 0;  // Количество переменных
    int M = 0;  // Количество неравенств
    fscanf(stdin, "%d %d", &N, &M);

    // Создаем матрицу смежности для графа
    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    // Заполняем матрицу смежности на основе неравенств
    for (int i = 0; i < M; i++) {
        int x = 0, y = 0;
        fscanf(stdin, "%d %d", &x, &y);
        matrix[x - 1][y - 1] = 1;  // x-1, y-1, т.к. индексация с 0
    }

    // Массив для отслеживания состояния вершин
    int *visited = (int*)calloc(N, sizeof(int));  // 0 - не посещена, 1 - в процессе, 2 - посещена
    int *sort = (int*)calloc(N, sizeof(int));  // Массив для хранения топологического порядка
    int index = 0;

    // Выполняем DFS для всех вершин
    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) {  // Если вершина еще не посещена
            if (!dfs(i, matrix, visited, N, sort, &index)) {
                printf("NO\n");
                return 0;  // Если цикл обнаружен
            }
        }
    }

    // Если цикл не найден, выводим результат
    printf("YES\n");

    // Выводим топологический порядок
    for (int i = N - 1; i >= 0; i--) {  // Мы строили порядок в обратном порядке
        printf("%d ", sort[i] + 1);  // Индексация с 1, поэтому +1
    }
    printf("\n");

    // Освобождаем память
    free(visited);
    free(sort);
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
