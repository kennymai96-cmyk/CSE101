//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA2
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
    int order; // define int holding order of graph(# of vertices)
    int u_edge; // define int holding # of undirected edges
    int d_edge; // define int holding # of directed edges
    int v_source; // define int holding most recent vertex source for BFS

    int* v_color; // int array holding the color of each vertex
    int* v_parent; // int array holding the parents of each vertex
    int* v_dist; // int array holding the distance from most recent source to vertex
    List* v_neighbors; // list array holding neighbors at each vertex
} GraphObj;

// constructors - destructors -------------------------------------------------

// newGraph()
// Returns a Graph having n vertices and no edges.
Graph newGraph(int n) {
    // allocate memory for Graph
    Graph G = malloc(sizeof(GraphObj)); 
    assert(G != NULL); 
    // init all ints
    G->order = n;
    G->u_edge = 0;
    G->d_edge = 0; 
    G->v_source = NIL; 
    // allocate memory for all arrays
    G->v_color = malloc((n + 1) * sizeof(int));
    G->v_parent = malloc((n + 1) * sizeof(int));
    G->v_dist = malloc((n + 1) * sizeof(int));
    G->v_neighbors = malloc((n + 1) * sizeof(List));
    // check for valid arrays
    assert(G->v_color && G->v_parent && G->v_dist && G->v_neighbors);
    // init each element of arrays(start at 1, 0 is NIL)
    for (int i = 1; i <= n; i++) {
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
        G->v_dist[i]      = INF;
        G->v_neighbors[i] = newList();
    }
    // return Graph with n vertices and no edges
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG) {
    free(*pG);
    *pG = NULL;
}

// access functions -----------------------------------------------------------

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->order;
}

// getNumEdges()
// Returns the number of edges in G.
int getNumEdges(Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->u_edge;
}

// getNumArcs()
// Returns the number of Arcs in G.
int getNumArcs(Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->u_edge;
}

// getSource()
// Returns the source vertex in the most recent call to BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // if BFS called, return source 
    if(G->v_source != NIL) { 
        return G->v_source;
    }
     else {
        return NIL;
    } 
}

// getParent
// Returns the parent of vertex u in the most recently constructed BFS tree
// or returns NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // if BFS called, return source 
    if(G->v_source != NIL) { 
        return G->v_parent[u];
    }
     else {
        return NIL;
    } 
    
}

// getDist()
// Returns the distance from the source vertex to u if BFS() has been called,
// otherwise returns INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // if BFS called, return source 
    if(G->v_source != NIL) { 
        return G->v_dist[u];
    }
     else {
        return INF;
    } 
}

// getPath()
// If vertex u is reachable from the source, appends the vertices of a shortest
// source-u path to List L. Otherwise, appends NIL to L.
// Pre: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }


}

// manipulation procedures ----------------------------------------------------
// makeNull()
// Resets G to its initial state.
void makeNull(Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // init all ints
    G->u_edge = 0;
    G->d_edge = 0; 
    G->v_source = NIL; 
    // check for valid arrays
    assert(G->v_color && G->v_parent && G->v_dist && G->v_neighbors);
    // init each element of arrays
    for (int i = 1; i <= G->order; i++) {
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
        G->v_dist[i]      = INF;
        G->v_neighbors[i] = newList();
    }
}

// addEdge()
// Creates an undirected edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertices
    if (!(1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G))) {
        fprintf(stderr, "Invalid vertices!\n");
        exit(EXIT_FAILURE);
    }
    // assign alias for u adj list
    List u_adj = G->v_neighbors[u];
    if(position(u_adj) == -1) { // if list is empty, insert the neighbor
        printf("Append u!\n");
        append(u_adj, v);  
        moveFront(u_adj);
    }
    else{
        moveFront(u_adj);
        while(position(u_adj) >= 0) {
            if(v < get(u_adj)) {
                insertBefore(u_adj, v);
                printf("Insert u!\n");
                break;
            }
            else{
                moveNext(u_adj);
            }
        }
    }
    // assign alias for v adj list
    List v_adj = G->v_neighbors[v];
    printf("Position before v branch: %d\n", position(v_adj));
    if(position(v_adj) == -1) { // if list is empty, insert the neighbor
        printf("Append v!\n");
        append(v_adj, u);  
        moveFront(v_adj);
    }
    else{
        moveFront(v_adj);
        while(position(v_adj) >= 0) {
            if(u < get(v_adj)) {
                printf("Insert v!\n");
                insertBefore(v_adj, u);
                break;
            }
            else{
                moveNext(v_adj);
            }
        }
    }
    printf("Position after v branch: %d\n", position(v_adj));

    // update edge count
    G->u_edge++;
}   

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
void printGraph(FILE* out, Graph G) {
    if(G == NULL) { // check that list exists
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < (G->order + 1); i++) {
        printf("%d: ", i);
        printList(stdout, G->v_neighbors[i]);
    } 
}