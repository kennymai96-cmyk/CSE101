//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA4
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------

#include <stdio.h> // required libraries
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Matrix.h"
#include "List.h"

// Defines private struct containing column & value info
typedef struct EntryObj{
    int col;
    double val;
} EntryObj; //alias

typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj{
    int n; // size n of matrix
    int nzn; // # of non-zero entries
    List* rows; // array of lists representing rows of Entries
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Create a new pointer to matrix entry info
static Entry newEntry(int col, double val){
    Entry E = malloc(sizeof(EntryObj));
    // check for valid entry
    if (E == NULL) {
        fprintf(stderr, "NULL Entry!\n");
        exit(EXIT_FAILURE);
    }
    // load entry values 
    E->col = col;
    E->val = val; 
    // return entry
    return E;
}

// newMatrix()
// Returns a reference to a new n by n Matrix in the zero state.
Matrix newMatrix(int n){

    Matrix M = malloc(sizeof(MatrixObj));
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Entry!\n");
        exit(EXIT_FAILURE);
    }
    // load matrix values
    M->n = n;
    // zero init matrix entries
    M->nzn = 0;
    for(int i = 0; i <= dimension(M); i++){
        M->rows[i] = 0;
    }
    // return new matrix
    return M;
}

// freeMatrix()
// Frees all heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);

// Access functions -----------------------------------------------------------

// dimension()
// Returns the number of rows and columns of square Matrix M.
int dimension(Matrix M);
// numNonZero()
// Returns the number of non-zero elements in M.
int numNonZero(Matrix M);
// equals()
// Returns true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B);
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Resets M to the zero Matrix.
void makeZero(Matrix M);
// changeEntry()
// Changes the ith row, jth column of M to be the value x.
// Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x);
// Matrix Arithmetic operations -----------------------------------------------
// copy()
// Returns a reference to a new Matrix having the same entries as A.
Matrix copy(Matrix A);
// transpose()
// Returns a reference to a new Matrix representing the transpose
// of A.
Matrix transpose(Matrix A);
// scalarMult()
// Returns a reference to a new Matrix representing xA.
Matrix scalarMult(double x, Matrix A);
// sum()
// Returns a reference to a new Matrix representing A+B.
// pre: dimension(A)==dimension(B)
Matrix sum(Matrix A, Matrix B);
// diff()
// Returns a reference to a new Matrix representing A-B.
// pre: dimension(A)==dimension(B)
Matrix diff(Matrix A, Matrix B);
// product()
// Returns a reference to a new Matrix representing AB
// pre: dimension(A)==dimension(B)
Matrix product(Matrix A, Matrix B);
// Other operations -----------------------------------------------------------
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows are
// not printed. Each non-zero row is represented as a line consisting of the
// row number, followed by a colon, a space, then a space separated list of pairs
// "(col, val)" giving the column numbers and non-zero values in that row. The
// double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);