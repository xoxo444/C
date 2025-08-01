#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, weight;
};

struct Edge* createEdgeList(int E) {
    return (struct Edge*)malloc(E * sizeof(struct Edge));
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]); // Path compression
}


void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
          
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
          
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}


int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}


void kruskal(struct Edge edges[], int V, int E) {
    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++)
        parent[i] = i;

    qsort(edges, E, sizeof(struct Edge), compareEdges);

    printf("\nEdges in Minimum Spanning Tree:\n");
    int totalWeight = 0, count = 0;

  
    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (find(parent, u) != find(parent, v)) {
            printf("%d - %d : %d\n", u, v, w);
            unionSets(parent, rank, u, v);
            totalWeight += w;
            count++;
        }
    }

    printf("Total Weight of MST: %d\n", totalWeight);

    free(parent);
    free(rank);
}



int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Edge* edges = createEdgeList(E);
    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal(edges, V, E);

    free(edges);
    return 0;
}
