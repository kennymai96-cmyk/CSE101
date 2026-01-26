//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA3
// FindComponents.c
// Top-level file for Graph ADT
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {  // check for valid amount of inputs: input file, output file and file name
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // FILE *in = stdin; 
    // FILE *out = stdout;
    FILE *in  = fopen(argv[1], "r");  // open input file for reading
    FILE *out = fopen(argv[2], "w");  // open output file for writing

    if (in == NULL || out == NULL) {  // check for valid input and output file
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char line[256]; // define line size
    int n; // define order

    fgets(line, sizeof(line), in); // get first line of input file
    sscanf(line, "%d", &n); // scan for order value
    Graph G = newGraph(n); // create graph with order value
    // printf("Order: %d\n", n);

    while (fgets(line, sizeof(line), in) != NULL) {  // read text from input file

        int u, v; // define vars to hold each input vertex

        if(sscanf(line, "%d %d", &u, &v) == 2) { // check for two vertices on each line
            if(u == 0 && v == 0) { // if two 0's, terminate read
                break; 
            }
            else {
                addArc(G, u, v); // define directed edge with two read vertices
            }
        }
    }
    // Run DFS on OG graph --> DFS on transpose graph using order from 1st DFS in list S
    // Each DFS in 2nd call correponds to one SCC from the 1st. We verify both for mutual reachability
    List S = newList(); // create new list to hold OG order of vertices, and then finished vertices
    for(int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }
    Graph T = transpose(G); // create transpose of G
    DFS(G, S); // run DFS on G
    DFS(T, S); // run DFS on T with vertices ordered by decreasing finish time

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    int SCC_count = 0; // define int to hold # of SCCs
    // iterate thru S and check which vertices are roots
    for(moveFront(S); position(S) >= 0; moveNext(S)) {
        int u = get(S);
        if(getParent(T, u) == NIL) {
            SCC_count++;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", SCC_count);
    
    List M = newList();
    int c_num = 0;
    // iterate backwards thru S in order of increasing finish time
    // check which vertices are roots, if not append to list and continue, navigates the SCC 
    for(moveBack(S); position(S) >= 0; movePrev(S)) {
        int u = get(S);
        prepend(M, u);
        // when root encountered, increment component count and build next SCC
        if(getParent(T, u) == NIL) {
            c_num++;
            fprintf(out, "Component %d: ", c_num);
            printList(out, M);
            fprintf(out, "\n");
            clear(M); 
        }
    }
    fprintf(out, "\n"); // print to output file

    freeGraph(&G); // free memory of GraphObj
    fclose(in); // close the input file
    fclose(out); // close the output file

    return 0;
}