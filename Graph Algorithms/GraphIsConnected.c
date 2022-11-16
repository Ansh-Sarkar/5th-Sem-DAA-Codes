#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct graph {
    int n;
    struct node **adjList;
};

struct graph *createGraph(int n) {
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    g->n = n;
    g->adjList = (struct node **)malloc(n * sizeof(struct node *));
    for (int i = 0; i < n; i++)
        g->adjList[i] = NULL;
    return g;
}

void addEdge(struct graph *g, int u, int v) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = v;
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = u;
    newNode->next = g->adjList[v];
    g->adjList[v] = newNode;
}

void printGraph(struct graph *g) {
    printf("Adjacency List:\n");
    for (int i = 0; i < g->n; i++) {
        printf("%d: ", i);
        struct node *temp = g->adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void dfs(struct graph *g, int u, int *visited) {
    visited[u] = 1;
    printf("%d ", u);
    struct node *temp = g->adjList[u];
    while (temp != NULL) {
        if (visited[temp->data] == 0)
            dfs(g, temp->data, visited);
        temp = temp->next;
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
    printf("DFS: ");
    int *visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    dfs(g, 0, visited);
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            printf("Graph is not connected\n");
            return 0;
        }
    }
    printf("Graph is connected\n");
}