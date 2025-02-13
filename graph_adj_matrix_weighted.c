#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define INF INT_MAX

// Graph structure with adjacency matrix
struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

// Function to initialize the graph
void initGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;

    // Initialize the adjacency matrix with 0 (no edges)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph (undirected graph)
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Error: Vertex out of bounds\n");
        return;
    }
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight; // For undirected graph
}

// Function to print the adjacency matrix
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function for DFS traversal
void dfs(struct Graph* graph, int vertex, int visited[]) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            dfs(graph, i, visited);
        }
    }
}

// Function to perform DFS traversal on the whole graph
void dfsTraversal(struct Graph* graph) {
    int visited[MAX_VERTICES] = {0}; // Initialize visited array

    // Perform DFS for each unvisited vertex
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited);
        }
    }
}

// Function for BFS traversal
void bfs(struct Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // Initialize visited array
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int vertex = queue[front++]; // Dequeue vertex
        printf("%d ", vertex);

        // Visit all adjacent vertices
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[vertex][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i; // Enqueue the adjacent vertex
            }
        }
    }
}

// Dijkstra's Algorithm to find the shortest path
void dijkstra(struct Graph* graph, int startVertex) {
    int dist[MAX_VERTICES]; // Distance array to store the shortest distance from the start vertex
    int visited[MAX_VERTICES]; // Visited array to keep track of processed vertices
    int prev[MAX_VERTICES]; // Array to store the previous vertex for each vertex in the path

    // Initialize distances, visited array, and prev array
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[startVertex] = 0;

    // Find the shortest path for each vertex
    for (int i = 0; i < graph->numVertices - 1; i++) {
        // Find the vertex with the minimum distance
        int minDist = INF;
        int u = -1;
        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        // Mark the selected vertex as visited
        visited[u] = 1;

        // Update the distances of adjacent vertices
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjMatrix[u][v] != 0 && !visited[v] && dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    // Print the shortest paths and distances
    printf("Shortest paths from vertex %d:\n", startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d: Distance = %d, Path = ", i, dist[i]);

        // Print the path from the start vertex to the current vertex
        int path[MAX_VERTICES];
        int pathLength = 0;
        for (int v = i; v != -1; v = prev[v]) {
            path[pathLength++] = v;
        }

        // Print the path in reverse order
        for (int j = pathLength - 1; j >= 0; j--) {
            printf("%d ", path[j]);
        }
        printf("\n");
    }
}

// Driver code
int main() {
    struct Graph graph;

    // Initialize the graph with 5 vertices
    initGraph(&graph, 5);

    // Add edges to the graph with weights
    addEdge(&graph, 0, 1, 10);
    addEdge(&graph, 0, 4, 5);
    addEdge(&graph, 1, 2, 1);
    addEdge(&graph, 1, 3, 2);
    addEdge(&graph, 2, 3, 4);
    addEdge(&graph, 4, 1, 3);
    addEdge(&graph, 4, 2, 9);
    addEdge(&graph, 4, 3, 2);

    // Print the adjacency matrix
    printf("Adjacency Matrix of the Graph:\n");
    printGraph(&graph);

    // Perform DFS traversal starting from vertex 0
    printf("\nDFS Traversal of the Graph:\n");
    dfsTraversal(&graph);

    // Perform BFS traversal starting from vertex 0
    printf("\nBFS Traversal of the Graph starting from vertex 0:\n");
    bfs(&graph, 0);

    // Perform Dijkstra's algorithm to find the shortest path from vertex 0
    printf("\nDijkstra's Algorithm for Shortest Path:\n");
    dijkstra(&graph, 0);

    return 0;
}
