#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int to;
    int time;
} Road;

void find_shortest_path(int start, int city_count, int **roads, long long *dist, int *prev) {
    int *visited = calloc(city_count + 1, sizeof(int));
    for (int i = 1; i <= city_count; i++) {
        dist[i] = LLONG_MAX;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 1; i <= city_count; i++) {
        int current = -1;
        for (int j = 1; j <= city_count; j++) {
            if (!visited[j] && (current == -1 || dist[j] < dist[current])) {
                current = j;
            }
        }
        if (dist[current] == LLONG_MAX) break;
        visited[current] = 1;

        for (int neighbor = 1; neighbor <= city_count; neighbor++) {
            if (roads[current][neighbor] != 0) {
                int time = roads[current][neighbor];
                if (dist[neighbor] > dist[current] + time) {
                    dist[neighbor] = dist[current] + time;
                    prev[neighbor] = current;
                }
            }
        }
    }
    free(visited);
}

void print_path(int start, int end, int *prev, int city_count) {
    int *path = calloc(city_count + 1, sizeof(int));
    int path_size = 0;
    int current = end;

    while (current != start) {
        path[path_size++] = current;
        current = prev[current];
    }
    path[path_size++] = start;

    printf("%d ", path_size);
    for (int i = path_size - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    free(path);
}

int main() {
    FILE *input = fopen("input.txt", "r");

    int city_count, road_count, path_queries, time_queries;
    fscanf(input, "%d %d %d %d", &city_count, &road_count, &path_queries, &time_queries);

    int **roads = calloc(city_count + 1, sizeof(int *));
    for (int i = 1; i <= city_count; i++) {
        roads[i] = calloc(city_count + 1, sizeof(int));
    }

    for (int i = 0; i < road_count; i++) {
        int from, to, time;
        fscanf(input, "%d %d %d", &from, &to, &time);
        roads[from][to] = time;
        roads[to][from] = time;
    }

    int *path_from = calloc(path_queries, sizeof(int));
    int *path_to = calloc(path_queries, sizeof(int));
    for (int i = 0; i < path_queries; i++) {
        fscanf(input, "%d %d", &path_from[i], &path_to[i]);
    }

    int *time_from = calloc(time_queries, sizeof(int));
    int *time_to = calloc(time_queries, sizeof(int));
    for (int i = 0; i < time_queries; i++) {
        fscanf(input, "%d %d", &time_from[i], &time_to[i]);
    }

    fclose(input);

    long long *dist = calloc(city_count + 1, sizeof(long long));
    int *prev = calloc(city_count + 1, sizeof(int));

    for (int i = 0; i < path_queries; i++) {
        int from = path_from[i];
        int to = path_to[i];
        find_shortest_path(from, city_count, roads, dist, prev);
        printf("%lld ", dist[to]);
        print_path(from, to, prev, city_count);
        printf("\n");
    }

    for (int i = 0; i < time_queries; i++) {
        int from = time_from[i];
        int to = time_to[i];
        find_shortest_path(from, city_count, roads, dist, prev);
        printf("%lld\n", dist[to]);
    }


    return 0;
}