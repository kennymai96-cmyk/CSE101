//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA2
// GraphTest.c
// Unit Tests for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

int main(void){

    int n = 4;
    int u = 1;
    int w = 2;
    int x = 3;
    int v = 4;

    Graph G = newGraph(n);

    // add edge tests
    /*addEdge(G, u, v);
    addEdge(G, u, w);
    addEdge(G, u, x);
    addEdge(G, v, w);
    addEdge(G, v, x);
    addEdge(G, w, x);
    printGraph(stdout, G);*/
    // freeGraph(&G);

    // add arc tests
    addArc(G, u, w); 
    addArc(G, w, x); 
    addArc(G, x, v); 
    printGraph(stdout, G);
    BFS(G, u);
    //List L = newList();
    //getPath(L, G, w);
    //printList(stdout, L);


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
    if(position(u_adj) == -1) { 
        append(u_adj, v);  
        moveFront(u_adj);
    }
    else{
        moveFront(u_adj);
        while(position(u_adj) >= 0) {
            if(v < get(u_adj)) {
                insertBefore(u_adj, v);
                break;
            }
            else{
                moveNext(u_adj);
            }
        }
    }
    // assign alias for v adj list
    List v_adj = G->v_neighbors[v];
    // if list is empty, insert the neighbor
    if(position(v_adj) == -1) { 
        append(v_adj, u);  
        moveFront(v_adj);
    }
    else{
        moveFront(v_adj);
        while(position(v_adj) >= 0) {
            if(u < get(v_adj)) {
                insertBefore(v_adj, u);
                break;
            }
            else{
                moveNext(v_adj);
            }
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
    if(position(u_adj) == -1) { // if list is empty, insert the neighbor
        append(u_adj, v);  
        moveFront(u_adj);
    }
    else{
        moveFront(u_adj);
        while(position(u_adj) >= 0) {
            if(v < get(u_adj)) {
                insertBefore(u_adj, v);
                break;
            }
            else{
                moveNext(u_adj);
            }
        }
    }
    // update edge count
    G->d_edge++;
}

    // printf("All List tests passed.\n");
    return 0;
}
