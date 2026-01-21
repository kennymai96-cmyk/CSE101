//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA2
// FindPath.c
// Top-level file for Graph ADT
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {  // check for valid amount of inputs: input file, output file and file name
    /*if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }*/

    FILE *in = stdin; 
    FILE *out = stdout;
    // FILE *in  = fopen(argv[1], "r");  // open input file for reading
    // FILE *out = fopen(argv[2], "w");  // open output file for writing

    if (in == NULL || out == NULL) {  // check for valid input and output file
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char line[256]; // define line size
    int n; // define order

    fgets(line, sizeof(line), in); // get first line of input file
    sscanf(line, "%d", &n); // scan for order value
    Graph G = newGraph(n); // create graph with order value
    printf("Order: %d\n", n);

    while (fgets(line, sizeof(line), in) != NULL) {  // read text from input file

        int u, v; // define vertex vars

        if(sscanf(line, "%d %d", &u, &v) == 2) { // check for two vertices on each line
            if(u == 0 && v == 0) { // if two 0's, terminate read
                break; 
            }
            else {
                addEdge(G, u, v); // define undirected edge with two read vertices
            }
        }
        printGraph(stdout, G);
    }


    // freeGraph(&G); // free memory of GraphObj
    fclose(in); // close the input file
    fclose(out); // close the output file

    return 0;
}