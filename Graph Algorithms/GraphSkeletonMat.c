#include<stdio.h>
#include<stdlib.h>

// structure to represent the graph
struct Graph {
    int n;
    int *adjMatrix;
};


// get or read a value from the adjacency matrix 
int getValMat(int i, int j, struct Graph *g) {
    return *(g->adjMatrix + (g->n) * i + j);
}

// put or update a value in the adjacency matrix
void putValMat(int i, int j, int val, struct Graph *g) {
    *(g->adjMatrix + (g->n) * i + j) = val;
}

// creates and returns the graph object
struct Graph createGraph(int nodes) {
    struct Graph g; g.n = nodes;
    g.adjMatrix = (int *) malloc(nodes * nodes * sizeof(int));
    for(int i = 0 ; i < nodes ; i++)
        for(int j = 0 ; j < nodes ; j++)
            putValMat(i, j, 0, &g);
    return g;
};

// add bidirectional edge to the graph
int addEdgeBi(int u, int v, struct Graph *g) {
    if((u < g->n && u > -1) && (v < g->n && v > -1)) {
        putValMat(u, v, 1, g);
        putValMat(v, u, 1, g);
        return 1;
    } return 0;
}

// add unidirectional edge to the graph
int addEdgeUni(int u, int v, struct Graph *g) {
    if((u < g->n && u > -1) && (v < g->n && v > -1)) {
        putValMat(u, v, 1, g);
        return 1;
    } return 0;
}

// function to print the adjacency matrix
void printAdjMat(struct Graph *g) {
    for(int i = 0 ; i < g->n ; i++) {
        for(int j = 0 ; j < g->n ; j++)
            printf("%d ", getValMat(i, j, g));
        printf("\n");
    }
}

int main() {
    int n; printf("Enter the number of nodes : "); scanf("%d", &n);
    int u, v, isValid = 1; struct Graph g = createGraph(n);
    while(isValid) {
        printf("Enter the nodes to be added to the Graph : ");
        scanf("%d%d", &u, &v); isValid = addEdgeUni(u, v, &g);
    }
    printf("The Adjacency Matrix is : \n");
    printAdjMat(&g);
    return 0;
}