#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, weight;
};

// Find the parent of a vertex
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;

    return parent[i] = find(parent, parent[i]);
}

// Union two sets
void unionSet(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);

    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Compare edges for sorting
int compare(const void *a, const void *b) {
    struct Edge *e1 = (struct Edge *)a;
    struct Edge *e2 = (struct Edge *)b;

    return e1->weight - e2->weight;
}

void kruskal(struct Edge edges[], int V, int E) {
    int parent[V];
    int rank[V];

    // Initially, every vertex is its own set
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges according to weight
    qsort(edges, E, sizeof(struct Edge), compare);

    int mstWeight = 0;
    int edgeCount = 0;

    printf("Edges in Minimum Spanning Tree:\n");

    for (int i = 0; i < E && edgeCount < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // Check whether adding this edge creates a cycle
        if (find(parent, u) != find(parent, v)) {
            printf("%d -- %d  = %d\n", u, v, edges[i].weight);

            mstWeight += edges[i].weight;
            edgeCount++;

            unionSet(parent, rank, u, v);
        }
    }

    printf("Minimum Cost = %d\n", mstWeight);
}

int main() {
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    struct Edge edges[E];

    printf("Enter edges (u v weight):\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].weight);
    }

    kruskal(edges, V, E);

    return 0;
}