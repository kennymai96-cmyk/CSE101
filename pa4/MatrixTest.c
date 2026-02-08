//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA4
// Matrix Test.c
// Unit Tests for Matrix ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Matrix.h"
#include "List.h"

int main(void){
    // make new matrix
    Matrix M = newMatrix(3);
    // add entry
    changeEntry(M, 1, 2, 3.0);
    changeEntry(M, 2, 1, 4.0);
    changeEntry(M, 2, 3, 6.0);
    printMatrix(stdout, M);
    printf("\n");
    // make new matrix
    Matrix N = copy(M);
    //printMatrix(stdout, N);
    Matrix O = transpose(M);
    printMatrix(stdout, O);
    // free matrix
    freeMatrix(&M);
    freeMatrix(&N);

    return 0;
}
