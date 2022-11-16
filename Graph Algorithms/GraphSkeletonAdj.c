#include<stdio.h>
#include<malloc.h>

// edges are directed by default u -> v
struct Edge {
    int u, v;
};

// Nodes are pushed into the adjacency list against keyNodes
struct Node {
    int val;
    struct Node *next;
};

// special node to store the list, has a tail pointer as well
// in order to allow for easy enqueueing into the adjList
struct keyNode {
    int val;
    struct Node *next, *tail;
};

// structure to store our graph data structure
struct Graph {
    int n;
    struct keyNode *adjList; 
};

// function to create and return the graph
struct Graph createGraph(int nodes) {
    struct Graph g; g.n = nodes;
    g.adjList = (struct keyNode *) malloc(nodes * sizeof(struct keyNode));
    for(int i = 0 ; i < nodes ; i++) { g.adjList[i].next = g.adjList[i].tail = NULL; g.adjList[i].val = i; }
    return g;
}

// enqueueing elements to the back of the list
void enqueueEnd(struct keyNode *k, int val) {
    // creating the newNode
    struct Node *newNode = (struct Node *) malloc(1 * sizeof(struct Node));
    newNode->val = val; newNode->next = NULL;
    // inserting the newNode either at the beginning if the list was empty
    // or inserting the newNode at the end if the list had atleast one element
    if(k->next == NULL && k->tail == NULL) k->next = k->tail = newNode;
    else { k->tail->next = newNode; k->tail = newNode; }
}

// enqueueing elements to the beginning of the list
void enqueueBeg(struct keyNode *k, int val) {
    // creating the newNode
    struct Node *newNode = (struct Node *) malloc(1 * sizeof(struct Node));
    newNode->val = val; newNode->next = NULL;
    // inserting the newNode either at the beginning if the list was empty
    // or inserting the newNode at the end if the list had atleast one element
    if(k->next == NULL && k->tail == NULL) k->next = k->tail = newNode;
    else { newNode->next = k->next; k->next = newNode; }
}

// function to add a unidirectional edge
int addUniEdge(int u, int v, struct Graph g) {
    if((u < g.n && u > -1) && (v < g.n && v > -1)) {
        enqueueEnd(&g.adjList[u], v);
        return 1;
    } return 0;
}


// function to add a bidirectional edge
int addBiEdge(int u, int v, struct Graph g) {
    if((u < g.n && u > -1) && (v < g.n && v > -1)) {
        enqueueEnd(&g.adjList[u], v);
        enqueueEnd(&g.adjList[v], u);
        return 1;
    } return 0;
}

// print the adjacency list form of the graph
void printAdjList(struct Graph g) {
    for(int i = 0 ; i < g.n ; i++) {
        printf("[%d]: ", g.adjList[i].val);
        struct Node *temp = g.adjList[i].next;
        while(temp) { printf("%d ", temp->val); temp = temp->next; };
        printf("\n");
    }
}

// sample driver code
int main() {
    int n; printf("Enter the number of nodes in the graph (0 based indexing) : "); scanf("%d", &n);
    struct Graph g = createGraph(n);
    int u = 1, v = 1, isValid = 1;
    while(isValid) {
        printf("Enter the nodes between whom the edge is to be added : ");
        scanf("%d%d", &u, &v); isValid = addUniEdge(u, v, g);
    }
    printAdjList(g);
    return 0;
}