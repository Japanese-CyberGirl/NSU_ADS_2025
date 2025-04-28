#include <stdio.h>
#include <stdlib.h>

#define max_n 100000

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node *adj_list[max_n + 1]; // список смежности
int in_degree[max_n + 1];  // входные степени вершин
int res_ord[max_n];        // топологический порядок
int res_size = 0;          // размер топологического порядка

// добавление ребра в список смежности
void add_edge(Node **adj, int from, int to) {
    Node *new_n = (Node *)malloc(sizeof(Node));
    new_n->vertex = to;
    new_n->next = adj[from];
    adj[from] = new_n;
}

// алгоритм Кана
int k_alg(int N) {
    int queue[max_n]; // очередь для вершин с нулевой входной степенью
    int front = 0;
    int rear = 0; // указатели для очереди

    // добавляем вершины с нулевой входной степенью в очередь
    for (int i = 1; i <= N; i++) {
        if (in_degree[i] == 0)
            queue[rear++] = i;
    }

    // пока очередь не пуста
    while (front < rear) {
        int u = queue[front++]; // извлекаем вершину
        res_ord[res_size++] = u; // добавляем в результат

        Node *current = adj_list[u];
        while (current != NULL) {
            int v = current->vertex;
            in_degree[v]--;  // уменьшаем входную степень вершины v
            if (in_degree[v] == 0) // если входная степень стала нулевой, добавляем в очередь
                queue[rear++] = v;
            current = current->next;
        }
    }
    return res_size == N; // если обработаны все вершины, то возвращаем TRUE
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // Инициализация списка смежности и степеней входа
    for (int i = 1; i <= N; i++) {
        adj_list[i] = NULL;
        in_degree[i] = 0;
    }

    // Чтение ребер и добавление их в граф
    for (int i = 0; i < M; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        add_edge(adj_list, from, to);
        in_degree[to]++;
    }

    // Выполнение алгоритма Кана
    if (!k_alg(N)) {
        printf("NO\n");
        return 0;
    }

    // Вывод результата
    printf("YES\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", res_ord[i]);
    }
    printf("\n");

    return 0;
}
