//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA4
// Sparse.c
// Top-level file for Matrix ADT
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Matrix.h"
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
    // define line size
    char line[256]; 
    // define matrix info vars
    int n, a, b; 
    // get first line of input file
    if(fgets(line, sizeof(line), in) == NULL){
        fprintf(stderr, "Incorrect header!");
        exit(EXIT_FAILURE);
    }
    // scan for matrix info
    if(sscanf(line, "%d %d %d", &n, &a, &b) != 3){
        fprintf(stderr, "Incorrect header format!");
        exit(EXIT_FAILURE);
    } 
    // define matrices
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    // scan matrix A info
    while((fgets(line, sizeof(line), in) != NULL) && a > 0){
        // define entry info vars
        int row, col;
        double val;
        // check for valid matrix A info
        if(sscanf(line, "%d %d %lf", &row, &col, &val) == 3) { 
            // load entry into A
            changeEntry(A, row, col, val);
            // decrement a nzn #
            a--;
            if(a == 0){
                break;
            }
        }
    }
    // check for newline inbtwn matrix A & B info
    while(fgets(line, sizeof(line), in) != NULL){
        // check for start of matrix B info
        if(line[0] != '\n' && line[0] != '\r'){
            // define entry info vars
            int row, col;
            double val;
            // check for valid matrix B info
            if(sscanf(line, "%d %d %lf", &row, &col, &val) == 3) {
                // load entry into B
                changeEntry(B, row, col, val);
             // decrement b nzn #
                b--;
            }
            // proceed to rest of matrix B info
            break;
        }
    }
    // scan matrix B info
    while((fgets(line, sizeof(line), in) != NULL) && b > 0){
        // define entry info vars
        int row, col;
        double val;
        // check for valid matrix B info
        if(sscanf(line, "%d %d %lf", &row, &col, &val) == 3) { 
            // load entry into matrix B
            changeEntry(B, row, col, val);
            // decrement b nzn #
            b--;
            if(b == 0){
                break;
            }
        }
    }
    // print matrix A info
    printMatrix(stdout, A);
    // print to output file
    fprintf(out, "\n"); 
    // close the input/output file
    fclose(in);
    fclose(out); 
    // return 0 to make main happy
    return 0;
}