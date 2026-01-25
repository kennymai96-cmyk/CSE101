//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA3
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
    int* v_disc; // define int array holding discover times of each vertex
    int* v_fin; // define int array holding finish times of each vertex
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
    G->v_disc = malloc((n + 1) * sizeof(int));
    G->v_fin = malloc((n + 1) * sizeof(int));
    G->v_neighbors = malloc((n + 1) * sizeof(List));
    // check for valid arrays
    assert(G->v_color && G->v_parent && G->v_dist && G->v_neighbors && G->v_disc && G->v_fin);
    // init each element of arrays(start at 1, 0 is NIL)
    for (int i = 1; i <= n; i++) {
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
        G->v_dist[i]      = INF;
        G->v_disc[i] = UNDEF;
        G->v_fin[i] = UNDEF;
        G->v_neighbors[i] = newList();
    }
    // return Graph with n vertices and no edges
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;
        // iterate thru adj lists and free memory
        for (int i = 1; i <= G->order; i++) {
            freeList(&G->v_neighbors[i]);
        }
        // free vertex info memory
        free(G->v_neighbors);
        free(G->v_color);
        free(G->v_parent);
        free(G->v_dist);
        free(G->v_disc);
        free(G->v_fin);
        // free GraphObj memory
        free(G);
        *pG = NULL;
    }
}

// access functions -----------------------------------------------------------

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->order;
}

// getNumEdges()
// Returns the number of edges in G.
int getNumEdges(Graph G) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->u_edge;
}

// getNumArcs()
// Returns the number of Arcs in G.
int getNumArcs(Graph G) {
    // check that Graph exists
    if(G == NULL) {
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    return G->d_edge;
}

// getSource()
// Returns the source vertex in the most recent call to BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G) {
    // check that Graph exists
    if(G == NULL) { 
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

// getDist()
// Returns the distance from the source vertex to u if BFS() has been called,
// otherwise returns INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertex
    if (u < 1 || u > getOrder(G)) { 
        fprintf(stderr, "Invalid vertex!\n");
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
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check that L exists
    if(L == NULL) { 
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertex
    if (u < 1 || u > getOrder(G)) { 
        fprintf(stderr, "Invalid vertex!\n");
        exit(EXIT_FAILURE);
    }
    // check if u is unreachable from source
    if(G->v_dist[u] == INF) {
        append(L, NIL);
        return;
    }
    // check if u is source
    if(u == G->v_source) {
        append(L, u);
        return;
    }
    // recursion to find shortest path
    getPath(L, G, G->v_parent[u]);
    append(L, u);
}

// getParent
// Returns the parent of vertex u, or NIL if DFS() not yet called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertex
    if (u < 1 || u > getOrder(G)) { 
        fprintf(stderr, "Invalid vertex!\n");
        exit(EXIT_FAILURE);
    }
    // if DFS called, return source 
    if(G->v_disc[u] == UNDEF) { 
        return NIL;
    }
     else {
        return G->v_parent[u];
    }   
}

// getDiscover()
// Returns the discover time of u, or UNDEF if DFS() not yet called.
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertex
    if (u < 1 || u > getOrder(G)) { 
        fprintf(stderr, "Invalid vertex!\n");
        exit(EXIT_FAILURE);
    }

    return G->v_disc[u];
}

// getFinish()
// Returns the finish time of u, or UNDEF if DFS() not yet called.
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid vertex
    if (u < 1 || u > getOrder(G)) { 
        fprintf(stderr, "Invalid vertex!\n");
        exit(EXIT_FAILURE);
    }

    return G->v_fin[u];
}


// manipulation procedures ----------------------------------------------------
// makeNull()
// Resets G to its initial state.
void makeNull(Graph G) {
    // check for valid vertex
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // init all vertex info
    G->u_edge = 0;
    G->d_edge = 0; 
    G->v_source = NIL; 
    // check for valid arrays
    assert(G->v_color && G->v_parent && G->v_dist && G->v_neighbors);
    // init each element of arrays
    for (int i = 1; i <= G->order; i++) {
        clear(G->v_neighbors[i]);
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
        G->v_dist[i]      = INF;
        G->v_disc[i] = UNDEF;
        G->v_fin[i] = UNDEF;
    }
}

// addEdge()
// Creates an undirected edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
// addEdge()
// Creates an undirected edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    // check for valid vertex
    if(G == NULL) { 
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
    // if list is empty, insert the neighbor
    if(length(u_adj) == 0) {
        append(u_adj, v);
    }
    else {
        moveFront(u_adj);
        while(position(u_adj) >= 0) {
            // insert before first larger element
            if(v < get(u_adj)) {
                insertBefore(u_adj, v);
                break;
            }
            moveNext(u_adj);
        }
        // v is larger than all existing neighbors
        if(position(u_adj) == -1) {
            append(u_adj, v);
        }
    }
    // assign alias for v adj list
    List v_adj = G->v_neighbors[v];
    // if list is empty, insert the neighbor
    if(length(v_adj) == 0) {
        append(v_adj, u);
    }
    else {
        moveFront(v_adj);
        while(position(v_adj) >= 0) {
            // insert before first larger element
            if(u < get(v_adj)) {
                insertBefore(v_adj, u);
                break;
            }
            moveNext(v_adj);
        }
        // u is larger than all existing neighbors
        if(position(v_adj) == -1) {
            append(v_adj, u);
        }
    }
    // update edge count
    G->u_edge++;
}
 

// addArc()
// Creates a directed edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
    // check that Graph exists
    if(G == NULL) { 
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
    // if list is empty, insert the neighbor
    if(length(u_adj) == 0) { 
        append(u_adj, v);  
    }
    else{
        // go to front of adj list
        moveFront(u_adj);
        // iterate while cursor is valid
        while(position(u_adj) >= 0) {
            if(v < get(u_adj)) {
                insertBefore(u_adj, v);
                // update edge count
                G->d_edge++;
                return;
            }
            else{
                moveNext(u_adj);
            }
        }
        // if v is larger that all neighbors
        append(u_adj, v);
    }
    // update edge count
    G->d_edge++;
}

// BFS()
// Runs the Breadth First Search algorithm on G with source vertex s.
void BFS(Graph G, int s) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > G->order) {
        fprintf(stderr, "Invalid vertex!\n");
        exit(EXIT_FAILURE);
    }
    // init all vertices in Graph as undiscovered
    for (int i = 1; i <= G->order; i++) {
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
        G->v_dist[i]      = INF;
    }
    // init source as discovered
    G->v_source = s;
    G->v_color[s]     = GRAY;
    G->v_parent[s]    = NIL;
    G->v_dist[s]      = 0;
    // create gray FIFO queue
    List FIFO = newList();
    // add source as oldest gray vertex
    append(FIFO, s);
    // explore while FIFO queue has gray vertices
    while(length(FIFO) > 0) {
        int x = front(FIFO); // assign vertex for exploration
        deleteFront(FIFO); // remove from gray vertices list

        List adj = G->v_neighbors[x]; // create adjacency list for current vertex
        // iterate thru the adjacency list of current vertex until position invalid
        for(moveFront(adj); position(adj) >= 0; moveNext(adj)) {
            int y = get(adj); // grab current neighbor
            if(G->v_color[y] == WHITE) { // check if undiscovered
                G->v_color[y] = GRAY; // set current vertex as discovered
                G->v_dist[y] = G->v_dist[x] + 1; // include x in y's path
                G->v_parent[y] = x; // set y's parent as x
                append(FIFO, y); // set y as next vertex to explore
            }
        }
        G->v_color[x] = BLACK; // set current vertex as finished
    }
    // free FIFO queue list
    freeList(&FIFO);
}

// Private helper function for DFS
// mark discover time
// recurse on neighbors
// mark finish time
static int Visit(Graph G, int u, List S, int time) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    time++; // increment time by 1 to mark entry into visit
    G->v_disc[u] = time; // save discovery time
    G->v_color[u] = GRAY; // set current vertex as discovered

    List u_adj = G->v_neighbors[u]; // create adj list for vertex u
    // iterate thru u's adjacency list 
    for(moveFront(u_adj); position(u_adj) >= 0; moveNext(u_adj)) {
        int v = get(u_adj); // grab current neighbor from u's adjacency list
        if(G->v_color[v] == WHITE) { // if undiscovered, connect to u and add to existing time
            G->v_parent[v] = u; 
            time = Visit(G, v, S, time); 
        }
    }

    G->v_color[u] = BLACK; // set current vertex as finished
    time++; // increment time by 1 to mark exploration complete
    G->v_fin[u] = time; // save finish time
    prepend(S, u); // place vertex into List S in reverse finish time order

    return time;
}

// DFS()
// Runs the Depth First Search algorithm on G. Input List S contains the vertex
// labels 1, .., n, where n=getOrder(G), and determines the order in which vertices
// are processed in the main loop of DFS(). When complete, output List S contains
// the same vertices sorted by decreasing finish times.
// Pre: getOrder(G)==getLength(S)
void DFS(Graph G, List S) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // check if vertex list equals order of Graph
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Invalid vertex list!\n");
        exit(EXIT_FAILURE);
    }
    // init all vertices in Graph as undiscovered 
    for(int i = 1; i <= G->order; i++) {
        G->v_color[i]     = WHITE;
        G->v_parent[i]    = NIL;
    } 

    int time = 0; // define int holding time

    List C = copyList(S); // copy list holding og order of vertices
    clear(S); // clear S for later insertion of reverse order finish times
    // iterate thru List S and catalog discovery/finish times
    for(moveFront(C); position(C) >= 0; moveNext(C)) {
        int u = get(C); // grab vertex to explore
        if(G->v_color[u] == WHITE) { // if undiscovered, begin exploring and recording time
            time = Visit(G, u, S, time); 
        }
    }

    freeList(&C); // free the copy List
}

// other functions ------------------------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to FILE* out.
void printGraph(FILE* out, Graph G) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < (G->order + 1); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->v_neighbors[i]);
        fprintf(out, "\n");
    } 
}

// copyGraph()
// Returns a copy of G.
Graph copyGraph(Graph G) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // make a copy graph with the same # of vertices
    Graph C = newGraph(G->order); 
    // iterate thru the adjacency list of og graph, and copy into copy graph
    for(int i = 1; i <= G->order; i++) {
        List G_adj = G->v_neighbors[i];
        List C_adj = C->v_neighbors[i];

        for(moveFront(G_adj); position(G_adj) >= 0; moveNext(G_adj)) {
            append(C_adj, get(G_adj)); 
        }
    }
    // copy edge counts
    C->u_edge = G->u_edge;
    C->d_edge = G->d_edge;

    return C;
}

// transpose()
// Returns the transpose of Graph G.
Graph transpose(Graph G) {
    // check that Graph exists
    if(G == NULL) { 
        fprintf(stderr, "NULL Graph!\n");
        exit(EXIT_FAILURE);
    }
    // make a transpose graph with the same # of vertices
    Graph T = newGraph(G->order); 
    // iterate thru the adjacency list of og graph and copy into temp list
    for(int i = 1; i <= G->order; i++) {
        List G_adj = G->v_neighbors[i];
        // iterate thru temp list and assign the neighbor vertex with the vertex we started from
        for(moveFront(G_adj); position(G_adj) >= 0; moveNext(G_adj)) {
            int v = get(G_adj); 
            append(T->v_neighbors[v], i); 
        }
    }
    // copy edge counts
    T->u_edge = G->u_edge;
    T->d_edge = G->d_edge;

    return T;
}