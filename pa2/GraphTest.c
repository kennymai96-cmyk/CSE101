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
    int v = 4;
    int w = 2;
    int x = 3;

    Graph G = newGraph(n);
    addEdge(G, u, v);
    addEdge(G, u, w);
    addEdge(G, u, x);
    addEdge(G, v, w);
    addEdge(G, v, x);
    addEdge(G, w, x);
    printGraph(stdout, G);
    // freeGraph(&G);


    // printf("All List tests passed.\n");
    return 0;
}
