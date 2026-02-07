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
    Matrix M = newMatrix(2);
    // add entry
    changeEntry(M, 1, 1, 5.0);
    changeEntry(M, 1, 2, 10.0);
    changeEntry(M, 2, 2, 15.0);
    changeEntry(M, 2, 1, 20.0);
    printMatrix(stdout, M);
    // make new matrix
    Matrix N = copy(M);
    printMatrix(stdout, N);
    // free matrix
    freeMatrix(&M);
    freeMatrix(&N);

    return 0;
}
