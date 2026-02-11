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
    // FILE *out = out;
    FILE *in  = fopen(argv[1], "r");  // open input file for reading
    FILE *out = fopen(argv[2], "w");  // open output file for writing

    if (in == NULL || out == NULL) {  // check for valid input and output file
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    // define line size
    char line[256]; 
    // define matrix info vars
    int n, a, b, a_nzn, b_nzn; 
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
    // copy a & b nzn #
    a_nzn = a;
    b_nzn = b;
    // define matrices
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    // scan matrix A info
    while((fgets(line, sizeof(line), in) != NULL) && a_nzn > 0){
        // define entry info vars
        int row, col;
        double val;
        // check for valid matrix A info
        if(sscanf(line, "%d %d %lf", &row, &col, &val) == 3) { 
            // load entry into A
            changeEntry(A, row, col, val);
            // decrement a nzn #
            a_nzn--;
            if(a_nzn == 0){
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
                b_nzn--;
            }
            // proceed to rest of matrix B info
            break;
        }
    }
    // scan matrix B info
    while((fgets(line, sizeof(line), in) != NULL) && b_nzn > 0){
        // define entry info vars
        int row, col;
        double val;
        // check for valid matrix B info
        if(sscanf(line, "%d %d %lf", &row, &col, &val) == 3) { 
            // load entry into matrix B
            changeEntry(B, row, col, val);
            // decrement b nzn #
            b_nzn--;
            if(b_nzn == 0){
                break;
            }
        }
    }
    // print matrix A
    fprintf(out, "A has %d non-zero entries:\n", a);
    printMatrix(out, A);
    fprintf(out, "\n");
    // print matrix B
    fprintf(out, "B has %d non-zero entries:\n", b);
    printMatrix(out, B);
    fprintf(out, "\n");
    // (1.5)*A
    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // A+B
    C = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // A+A
    C = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // B-A
    C = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // A-A
    C = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // Transpose(A)
    C = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // A*B
    C = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free previous matrix C
    freeMatrix(&C);
    // B*B
    C = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    // free all matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    // close the input/output file
    fclose(in);
    fclose(out); 
    // return 0 to make main happy
    return 0;
}