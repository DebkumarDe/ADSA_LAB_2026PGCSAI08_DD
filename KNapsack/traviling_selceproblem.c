
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int cost[MAX][MAX];
int visited[MAX];

int tsp(int n) {
    int current = 0;
    int totalCost = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[current] = 1;

    printf("Tour: 0 ");

    for (int count = 1; count < n; count++) {
        int next = -1;
        int minCost = 999999;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[current][j] < minCost) {
                minCost = cost[current][j];
                next = j;
            }
        }

        if (next == -1)
            return -1;

        totalCost += minCost;
        current = next;
        visited[current] = 1;

        printf("-> %d ", current);
    }

    totalCost += cost[current][0];
    printf("-> 0\n");

    return totalCost;
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};
    int tests = 5;

    printf("Nodes\tTime (seconds)\tTour Cost\n");

    for (int k = 0; k < tests; k++) {
        int n = sizes[k];

        srand(42);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    cost[i][j] = 0;
                else
                    cost[i][j] = rand() % 100 + 1;
            }
        }

        clock_t start = clock();

        int result = tsp(n);

        clock_t end = clock();

        double timeTaken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%.8f\t%d\n", n, timeTaken, result);
    }

    return 0;
}
