#include <stdio.h>
#include <limits.h>

#define MAX 100

void prim(int graph[MAX][MAX], int n)
{
    int selected[MAX] = {0};
    int parent[MAX];
    int key[MAX];

    int i, j, u;
    int totalCost = 0;

    // Initialize
    for (i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    // Start from vertex 0
    key[0] = 0;

    for (i = 0; i < n; i++) {

        int min = INT_MAX;
        u = -1;

        // Find vertex with minimum key
        for (j = 0; j < n; j++) {
            if (!selected[j] && key[j] < min) {
                min = key[j];
                u = j;
            }
        }

        // Add vertex to MST
        selected[u] = 1;

        // Update adjacent vertices
        for (j = 0; j < n; j++) {
            if (graph[u][j] != 0 &&
                !selected[j] &&
                graph[u][j] < key[j]) {

                key[j] = graph[u][j];
                parent[j] = u;
            }
        }
    }

    // Print MST
    printf("\nEdges in Minimum Spanning Tree:\n");

    for (i = 1; i < n; i++) {
        printf("%d - %d : %d\n",
               parent[i], i, graph[i][parent[i]]);

        totalCost += graph[i][parent[i]];
    }

    printf("Minimum Cost = %d\n", totalCost);
}

int main()
{
    int graph[MAX][MAX];
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    prim(graph, n);

    return 0;
}