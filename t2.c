#include <stdio.h>
#include <limits.h>

#define MAX_N 301
#define INF (LLONG_MAX / 2)

long long dist[MAX_N][MAX_N];
int next_node[MAX_N][MAX_N];

void reconstruct_path(int s, int t, FILE *output) {
    if (next_node[s][t] == -1) {
        fprintf(output, "%lld 0\n", dist[s][t]); 
    }

    int path[MAX_N];
    int len = 0;
    int current = s;

    path[len++] = current;
    while (current != t) {
        current = next_node[current][t];
        if (current == -1) break;
        path[len++] = current;
    }

    fprintf(output, "%lld %d", dist[s][t], len);
    for (int i = 0; i < len; ++i) {
        fprintf(output, " %d", path[i]);
    }
    fprintf(output, "\n");
}

int main() {

    FILE *input = fopen("input.txt", "r");


    int N, M, P, K;
    fscanf(input, "%d %d %d %d", &N, &M, &P, &K);

  
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            dist[i][j] = (i == j) ? 0 : INF;
            next_node[i][j] = -1;
        }
    }

 
    for (int i = 0; i < M; ++i) {
        int u, v, l;
        fscanf(input, "%d %d %d", &u, &v, &l);
        if (l < dist[u][v]) {
            dist[u][v] = l;
            next_node[u][v] = v;
        }
        if (l < dist[v][u]) {
            dist[v][u] = l;
            next_node[v][u] = u;
        }
    }


    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k];
                }
            }
        }
    }


    for (int i = 0; i < P + K; ++i) {
        int s, t;
        fscanf(input, "%d %d", &s, &t);
        if (i < P) {
            reconstruct_path(s, t, stdout);  
        } else {
            printf("%lld\n", dist[s][t]);   
        }
    }

    fclose(input);
    return 0;
}
