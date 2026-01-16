//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA2
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h> // required libraries
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
    int order; // define int holding order of graph(# of vertices)
    int arcs; // define int holding # of directed edges
    char* v_label; // define string pointer holding most recent source for BFS
    List* v_neighbors; // array holding neighbors at each vertex
    int* v_color; // array holding the color of each vertex
    int* v_parent; // array holding the parents of each vertex
    int* v_dist; // array holding the distance from most recent source to vertex
} GraphObj; //alias

// constructors - destructors -------------------------------------------------

// newGraph()
// Returns a Graph having n vertices and no edges.
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj)); //allocate memory for a new Graph
    assert(G != NULL); // if malloc fails, blow up program;
    G->order = NULL; 
    G->arcs = 0; 
    G->v_label = malloc((G->order + 1) * sizeof(char*));
    G->v_neighbors = malloc((G->order + 1) * sizeof(List*));
    G->v_color = malloc((G->order + 1) * sizeof(int*));
    G->v_parent = malloc((G->order + 1) * sizeof(int*));
    G->v_dist = malloc((G->order + 1) * sizeof(int*));
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG);

// access functions -----------------------------------------------------------

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G);

// getNumEdges()
// Returns the number of edges in G.
int getNumEdges(Graph G);

// getNumArcs()
// Returns the number of Arcs in G.
int getNumArcs(Graph G);

// getSource()
// Returns the source vertex in the most recent call to BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G);

// getParent
// Returns the parent of vertex u in the most recently constructed BFS tree
// or returns NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the source vertex to u if BFS() has been called,
// otherwise returns INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// If vertex u is reachable from the source, appends the vertices of a shortest
// source-u path to List L. Otherwise, appends NIL to L.
// Pre: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u);

// manipulation procedures ----------------------------------------------------
// makeNull()
// Resets G to its initial state.
void makeNull(Graph G);

// addEdge()
// Creates an undirected edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Creates a directed edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// Runs the Breadth First Search algorithm on G with source vertex s.
void BFS(Graph G, int s);
// other functions ------------------------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to FILE* out.
void printGraph(FILE* out, Graph G);