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
    Matrix M = newMatrix(1);
    // add entry
    changeEntry(M, 1, 1, 5.0);
    printMatrix(stdout, M);
    // free matrix
    freeMatrix(&M);

    return 0;
}
