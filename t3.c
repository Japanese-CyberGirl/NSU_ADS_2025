#include <stdio.h>
#include <stdlib.h>

void floyd(int **matrix, int N) {
    for (int k = 0; k < N; k++) {           // Промежуточная вершина k
        for (int i = 0; i < N; i++) {       // Исходная вершина i
            for (int j = 0; j < N; j++) {   // Целевая вершина j
                if (matrix[i][k] && matrix[k][j]) {  // Если есть путь через k
                    matrix[i][j] = 1;       // Устанавливаем связь
                }
            }
        }
    }
}

int main() {
    // Открываем файл для чтения
    if (freopen("input.txt", "r", stdin) == NULL) {
        fprintf(stderr, "Не удалось открыть файл input.txt\n");
        return 1; // Ошибка при открытии файла
    }

    int N = 0;
    fscanf(stdin, "%d", &N);  // Читаем размер матрицы

    // Выделяем память для матрицы
    int **matrix = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)calloc(N, sizeof(int));
    }

    // Чтение матрицы смежности
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(stdin, "%d", &matrix[i][j]);
        }
    }

    // Применяем рефлексивность (связь вершины с самой собой)
    for (int i = 0; i < N; i++) {
        matrix[i][i] = 1;
    }

    // Применяем алгоритм Флойда-Уоршалла для транзитивности
    floyd(matrix, N);

    // Выводим результат (рефлексивно-транзитивное замыкание)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
