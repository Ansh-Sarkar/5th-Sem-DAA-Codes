#include<stdio.h>
#include<stdlib.h>

struct Node {
    int n;
    struct Node *next;
};

struct Graph {
    int nodes, edges;
    struct Node *adjList;
};

void initializeAdjList(int n, struct Node *adjList) {
    for(int i = 0 ; i <= n ; i++) {
        adjList[i].n = i;
        adjList[i].next = NULL;
    }
}

void addElementAtEnd(struct Node *adjList, int a, int b) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->n = b;
    struct Node *temp = &adjList[a];
    while(temp->next) temp = temp->next;
    temp->next = newNode;
    printf("Added Edge %d -> %d\n", a, b);
}

int checkIfExists(struct Node *adjList, int a, int b) {
    struct Node *head = &adjList[a];
    while(head != NULL) {
        if(head->n == b) return 1;
        head = head->next;
    }
    return 0;
}

void addUnidirectionalEdge(struct Node *adjList, int a, int b) {
    if(checkIfExists(adjList, a, b)) {
        printf("Edge already exists !\n");
        return;
    }
    addElementAtEnd(adjList, a, b);
}

void printList(struct Node *adjList, int node) {
    struct Node *head = &adjList[node];
    while(head != NULL) {
        printf("%d ", head->n);
        head = head->next;
    }
}

void printAdjList(int n, struct Node *adjList) {
    for(int i = 1 ; i <= n ; i++) {
        printf("Node %d : ", i);
        printList(adjList, i);
        printf("\n");
    }
}

// helper function for dfs
void helper(int node, int n, struct Node *adjList, int *visited) {
    if (!visited[node]) {
        visited[node] = 1;
        printf("%d ", node);
        struct Node *neighbours = &adjList[node];
        while (neighbours) {
            helper(neighbours->n, n, adjList, visited);
            neighbours = neighbours->next;
        }
    }
}

// iterating over all nodes in order to make sure that even not connected components
// are detected.
void dfs(int n, struct Node *adjList, int *visited) {
    helper(1, n, adjList, visited);
}

int main() {
    int n;
    printf("Enter the number of nodes in the graph : ");
    scanf("%d", &n);

    struct Graph *g = (struct Graph *) malloc(sizeof(struct Graph));
    g->adjList = (struct Node *) malloc((n + 1) * sizeof(struct Node));
    g->nodes = n; g->edges = 0;

    initializeAdjList(n, g->adjList);

    printf("The graph has been initialized, you can now go ahead and add edges.\n");
    printf("Enter an invalid edge to exit (-1, -1)\n");
    int a = 1, b = 1;
    while(1) {
        printf("Enter edge (a , b): ");
        scanf("%d%d", &a, &b);
        if(!(a >= 1 && a <= n && b >= 1 && b <= n)) break;
        addUnidirectionalEdge(g->adjList, a, b);
    }

    printAdjList(n, g->adjList);

    printf("Printing the DFS traversal of the graph : ");
    int *visited = (int *) malloc((n + 1) * sizeof(int));
    for(int i = 0 ; i <= n ; i++) visited[i] = 0;

    dfs(n, g->adjList, visited);

    int isDisconnected = 0;
    for(int i = 1 ; i <= n ; i++) {
        if(!visited[i]) {
            isDisconnected = 1;
            break;
        }
    }
    if(isDisconnected) printf("The graph is Disconnected");
    else printf("The Graph is Connected");

    printf("\n");
    return 0;
}