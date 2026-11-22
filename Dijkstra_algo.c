
#include <stdio.h>
#define INF 99999

int main() {
    int n, i, j, source;
    int cost[20][20], dist[20], visited[20];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost adjacency matrix:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            if(cost[i][j] == 0 && i != j)
                cost[i][j] = INF;
        }
    }

    printf("Enter source vertex (0 to %d): ", n-1);
    scanf("%d", &source);

    for(i = 0; i < n; i++) {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;

    for(i = 1; i < n; i++) {
        int min = INF, u = -1;

        for(j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if(u == -1)
            break;

        visited[u] = 1;

        for(j = 0; j < n; j++) {
            if(!visited[j] &&
               cost[u][j] != INF &&
               dist[u] + cost[u][j] < dist[j]) {

                dist[j] = dist[u] + cost[u][j];
            }
        }
    }

    printf("\nShortest distances from source %d:\n", source);

    for(i = 0; i < n; i++) {
        if(dist[i] == INF)
            printf("%d -> %d = No path\n", source, i);
        else
            printf("%d -> %d = %d\n", source, i, dist[i]);
    }

    return 0;
}
