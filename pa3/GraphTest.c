//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA3
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
    ///printGraph(stdout, G);
    List S = newList();
    //getPath(L, G, w);

    //printList(stdout, L);

    DFS(G, S);


    // printf("All List tests passed.\n");
    return 0;
}
