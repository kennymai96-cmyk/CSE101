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
    Matrix A = newMatrix(3);
    // add entry
    changeEntry(A, 1, 1, 2.0);
    changeEntry(A, 1, 2, 3.0);
    printf("Matrix A: \n");
    printMatrix(stdout, A);
    printf("\n");
    // make new matrix
    Matrix B = copy(A);
    printf("Matrix B: \n");
    printMatrix(stdout, B);
    //Matrix O = transpose(M);
    //double x = 2;
    //Matrix O = scalarMult(x, M);
    Matrix C = sum(A, B);
    printf("\n");
    printf("Matrix C: \n");
    printMatrix(stdout, C);
    Matrix D = diff(C, B);
    printf("\n");
    printf("Matrix D: \n");
    printMatrix(stdout, D);
    Matrix E = product(C, D);
    printf("\n");
    printf("Matrix E: \n");
    printMatrix(stdout, E);
    // free matrix
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);

    return 0;
}
