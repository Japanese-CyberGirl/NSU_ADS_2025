#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Failed to open input file\n");
        return 1;
    }

    int total_nodes;
    fscanf(input_file, "%d", &total_nodes);

    int start_node, end_node;
    fscanf(input_file, "%d %d", &start_node, &end_node);

    int** connection_matrix = (int**)malloc((total_nodes + 1) * sizeof(int*));
    for (int i = 0; i <= total_nodes; i++) {
        connection_matrix[i] = (int*)malloc((total_nodes + 1) * sizeof(int));
        for (int j = 0; j <= total_nodes; j++) {
            connection_matrix[i][j] = 0;
        }
    }

    int node_a, node_b, transfer_time;
    while (fscanf(input_file, "%d %d %d", &node_a, &node_b, &transfer_time) == 3) {
        connection_matrix[node_a][node_b] = transfer_time;
        connection_matrix[node_b][node_a] = transfer_time;
    }
    fclose(input_file);

    int* min_times = (int*)calloc((total_nodes + 1), sizeof(int));
    int* processed_nodes = (int*)calloc((total_nodes + 1), sizeof(int));

    for (int i = 1; i <= total_nodes; i++) {
        min_times[i] = 999999;
        processed_nodes[i] = 0;
    }
    min_times[start_node] = 0;

    for (int iteration = 0; iteration < total_nodes; iteration++) {
        int current_min = 999999;
        int current_node = -1;
        
        for (int i = 1; i <= total_nodes; i++) {
            if (!processed_nodes[i] && min_times[i] < current_min) {
                current_min = min_times[i];
                current_node = i;
            }
        }

        if (current_node == -1) break;

        processed_nodes[current_node] = 1;

        for (int neighbor = 1; neighbor <= total_nodes; neighbor++) {
            if (!processed_nodes[neighbor] && connection_matrix[current_node][neighbor] > 0) {
                if (min_times[current_node] + connection_matrix[current_node][neighbor] < min_times[neighbor]) {
                    min_times[neighbor] = min_times[current_node] + connection_matrix[current_node][neighbor];
                }
            }
        }
    }

    if (min_times[end_node] != 999999) {
        printf("%d\n", min_times[end_node]);
    } else {
        printf("no\n");
    }

    for (int i = 0; i <= total_nodes; i++) {
        free(connection_matrix[i]);
    }
    free(connection_matrix);
    free(min_times);
    free(processed_nodes);

    return 0;
}