/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Shawn Singharaj
 * Email: singhars@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

#define DATA_FILE "airports.dat"

struct node {
	int vertex;
	int weight;
	struct node* next;
};
  

struct Graph{
	int numVertices;         // number of vertices in the graph
	struct node** adjLists;  // list of adjacent vertices for each vertex
	int* visited;  
};

struct node* createNode(int v, int weight) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int n) {
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->numVertices = n;     // number of vertices in the graph
  
	graph->adjLists = malloc(n * sizeof(struct node*));
	graph->visited = malloc(n * sizeof(int));
  
	for (int i = 0; i < n; i++) {
	  graph->adjLists[i] = NULL;    // adjacency lists are empty
	  graph->visited[i] = 0;        // visited initialized to 0
	}
  
	return graph;
}

/* Add edges to an exisiting undirected graph
   The edge (u,v) must be added to both u's and v's 
   adjacency lists                                */

void addEdge(struct Graph* graph, int u, int v, int w) {
	// Add edge from u to v
	struct node* newNode = createNode(v, w);
	newNode->next = graph->adjLists[u];
	graph->adjLists[u] = newNode;
  
	// Add edge from v to u
	newNode = createNode(u, w);
	newNode->next = graph->adjLists[v];
	graph->adjLists[v] = newNode;
}

int main(int argc, char const *argv[]) {
	
	int n_nodes, n_edges;
	FILE* file = fopen(DATA_FILE, "r");
	fscanf(file, " %d %d ", &n_nodes, &n_edges);
	
	struct Graph* graph = createGraph(n_edges);


	for(int i = 0; i < n_edges; i++){
		int u, v, w;
		fscanf(file, "%d %d %d", &u, &v, &w);
		
		addEdge(graph, u, v, w);
	}


	fclose(file);

	 
  return 0;
}
