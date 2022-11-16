#include <stdio.h>
#include <stdlib.h>

struct queue {
    int items[40];
    int front;
    int rear;
};

struct queue *createQueue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->front = q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(struct queue *q) {
    if (q->rear == -1) return 1;
    else return 0;
}

void enqueue(struct queue *q, int value) {
    if (q->rear == 39) printf("\nQueue is Full!!");
    else {
        if (q->front == -1) q->front = 0;
        q->rear++; q->items[q->rear] = value;
    }
}

int dequeue(struct queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    }
    else {
        item = q->items[q->front]; q->front++;
        if (q->front > q->rear) q->front = q->rear = -1;
    }
    return item;
}

struct node {
    int vertex;
    struct node *next;
};

struct graph {
    int num;
    struct node **adj_list;
    int *visited;
};

struct node *createNode(int v) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct graph *createGraph(int vertices) {
    struct graph *g = malloc(sizeof(struct graph));
    g->num = vertices;
    g->adj_list = malloc(vertices * sizeof(struct node *));
    g->visited = malloc(vertices * sizeof(int));
    int i;
    for (i = 0; i < vertices; i++) g->adj_list[i] = NULL;
    return g;
}

void addEdge(struct graph *g, int i, int j) {
    struct node *newNode = createNode(j);
    struct node *temp = newNode->next = g->adj_list[i];
    g->adj_list[i] = newNode;
    newNode = createNode(i);
    newNode->next = g->adj_list[j];
    g->adj_list[j] = newNode;
}

void printList(struct graph *g) {
    int v;
    for (v = 0; v < g->num; v++) {
        struct node *temp = g->adj_list[v];
        printf("\n Vertex %d: ", v);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
    }
}

void bfs(struct graph *g, int start) {
    struct queue *q = createQueue();
    g->visited[start] = 1;
    enqueue(q, start);
    while (!isEmpty(q)) {
        int curr = dequeue(q);
        printf("Visited %d\n", curr);
        struct node *temp = g->adj_list[curr];
        while (temp) {
            int adj_vertex = temp->vertex;
            if (g->visited[adj_vertex] == 0) {
                g->visited[adj_vertex] = 1;
                enqueue(q, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    struct graph *Graph = createGraph(7);
    int q, fr, to;
    addEdge(Graph, 0, 2);
    addEdge(Graph, 1, 4);
    addEdge(Graph, 1, 3);
    addEdge(Graph, 2, 6);
    addEdge(Graph, 2, 5);
    addEdge(Graph, 2, 1);
    bfs(Graph, 0);
    printList(Graph);

    printf("\n");
    return 0;
}