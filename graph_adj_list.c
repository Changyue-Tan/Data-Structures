#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

// Define a structure for the adjacency list node
struct Node {
	int vertex;
	struct Node *next;
};

// Graph structure with an adjacency list
struct Graph {
	int numVertices;
	struct Node **adjLists;  // Array of adjacency lists
};

// Function to create a new adjacency list node
struct Node *createNode(int vertex) {
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

// Function to initialize the graph
void initGraph(struct Graph *graph, int vertices) {
	graph->numVertices = vertices;

	// Allocate memory for adjacency lists
	graph->adjLists = (struct Node **)malloc(vertices * sizeof(struct Node *));

	// Initialize each adjacency list as NULL
	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}
}

// Function to add an edge to the graph (undirected graph)
void addEdge(struct Graph *graph, int src, int dest) {
	// Add an edge from src to dest
	struct Node *newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;

	// Add an edge from dest to src (undirected graph)
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
}

// Function to print the graph (adjacency list)
void printGraph(struct Graph *graph) {
	for (int i = 0; i < graph->numVertices; i++) {
		struct Node *temp = graph->adjLists[i];
		printf("Vertex %d: ", i);
		while (temp) {
			printf("%d -> ", temp->vertex);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

// Function for DFS traversal
void dfs(struct Graph *graph, int vertex, int visited[]) {
	printf("%d ", vertex);
	visited[vertex] = 1;

	struct Node *temp = graph->adjLists[vertex];
	while (temp) {
		if (!visited[temp->vertex]) {
			dfs(graph, temp->vertex, visited);
		}
		temp = temp->next;
	}
}

// Function to perform DFS traversal on the whole graph
void dfsTraversal(struct Graph *graph) {
	int visited[graph->numVertices];
	for (int i = 0; i < graph->numVertices; i++) {
		visited[i] = 0;
	}

	// Perform DFS for each unvisited vertex
	for (int i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {
			dfs(graph, i, visited);
		}
	}
}

// Function for BFS traversal
void bfs(struct Graph *graph, int startVertex) {
	bool visited[graph->numVertices];
	for (int i = 0; i < graph->numVertices; i++) {
		visited[i] = false;
	}

	// Create a queue for BFS
	int queue[graph->numVertices];
	int front = -1, rear = -1;

	// Start with the given vertex
	visited[startVertex] = true;
	queue[++rear] = startVertex;

	while (front != rear) {
		int vertex = queue[++front];
		printf("%d ", vertex);

		// Traverse the adjacent vertices
		struct Node *temp = graph->adjLists[vertex];
		while (temp) {
			if (!visited[temp->vertex]) {
				visited[temp->vertex] = true;
				queue[++rear] = temp->vertex;
			}
			temp = temp->next;
		}
	}
}

// Function to find the shortest path from a source vertex using BFS
void shortestPath(struct Graph *graph, int startVertex) {
	int distance[MAX_VERTICES];
	int parent[MAX_VERTICES];
	bool visited[MAX_VERTICES];

	// Initialize distances and parents
	for (int i = 0; i < graph->numVertices; i++) {
		distance[i] = -1;  // -1 means not visited
		parent[i] = -1;
		visited[i] = false;
	}

	// Create a queue for BFS
	int queue[graph->numVertices];
	int front = -1, rear = -1;

	// Start with the given vertex
	visited[startVertex] = true;
	distance[startVertex] = 0;
	queue[++rear] = startVertex;

	while (front != rear) {
		int vertex = queue[++front];

		// Traverse the adjacent vertices
		struct Node *temp = graph->adjLists[vertex];
		while (temp) {
			if (!visited[temp->vertex]) {
				visited[temp->vertex] = true;
				distance[temp->vertex] = distance[vertex] + 1;
				parent[temp->vertex] = vertex;
				queue[++rear] = temp->vertex;
			}
			temp = temp->next;
		}
	}

	// Print the shortest distances and paths
	for (int i = 0; i < graph->numVertices; i++) {
		if (distance[i] != -1) {
			printf("Shortest path from %d to %d: ", startVertex, i);
			printf("Distance = %d, Path = ", distance[i]);
			int current = i;
			while (current != -1) {
				printf("%d ", current);
				current = parent[current];
			}
			printf("\n");
		} else {
			printf("No path from %d to %d\n", startVertex, i);
		}
	}
}

// Driver code
int main() {
	struct Graph graph;
	initGraph(&graph, 5);

	// Add edges to the graph
	addEdge(&graph, 0, 1);
	addEdge(&graph, 0, 4);
	addEdge(&graph, 1, 2);
	addEdge(&graph, 1, 3);
	addEdge(&graph, 2, 3);

	// Print the adjacency list
	printf("Graph represented as an adjacency list:\n");
	printGraph(&graph);

	// Perform DFS traversal starting from vertex 0
	printf("\nDFS Traversal of the Graph:\n");
	dfsTraversal(&graph);

	// Perform BFS traversal starting from vertex 0
	printf("\nBFS Traversal of the Graph starting from vertex 0:\n");
	bfs(&graph, 0);

	// Find the shortest path from vertex 0
	printf("\nShortest Paths from vertex 0:\n");
	shortestPath(&graph, 0);

	return 0;
}
