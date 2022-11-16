#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct graph {
    int n;
    int **adjMatrix;
};

struct graph *createGraph(int n) {
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    g->n = n;
    g->adjMatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        g->adjMatrix[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            if(i==j)
                g->adjMatrix[i][j]=0;
            else
                g->adjMatrix[i][j]=INT_MAX;
        }
    return g;
}

void addEdge(struct graph *g, int u, int v) {
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}


void floydWarshall(struct graph *g) {
    int n = g->n;
    int dist[n][n];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = g->adjMatrix[i][j];
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printf("The shortest distance between every pair of vertices is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            if(dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}


void printGraph(struct graph *g) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++){
            if(g->adjMatrix[i][j] == INT_MAX)
                printf("0 ");
            else
                printf("%d ", g->adjMatrix[i][j]);

        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    struct graph *g = createGraph(n);
    int u, v;
    printf("Enter the edges (u, v) (-1 -1 to stop): \n");
    scanf("%d %d", &u, &v);
    while (u != -1 && v != -1) {
        addEdge(g, u, v);
        scanf("%d %d", &u, &v);
    }
    printGraph(g);
    floydWarshall(g);
}