//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA4
// Matrix.c
// ImpMementation file for Matrix ADT
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
    // check for min matrix size
    if(n < 1){
        fprintf(stderr, "Matrix too tiny!");
        exit(EXIT_FAILURE);
    }
    Matrix M = malloc(sizeof(MatrixObj));    
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // load matrix values
    M->n = n;
    M->nzn = 0;
    // allocate memory & zero-init matrix rows
    M->rows = calloc(n + 1, sizeof(List));
    // check for valid row allocation, and pMug memory leak if not
    if(M->rows == NULL){
        free(M);
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // create new list for each row of matrix
    for(int i = 1; i <= n; i++){
        M->rows[i] = newList();
    }
    // return new matrix
    return M;
}

// freeMatrix()
// Frees all heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    // check for valid matrix pointer
    if(pM == NULL || *pM == NULL){
        fprintf(stderr, "NULL MAtrix pointer!\n");
        exit(EXIT_FAILURE);
    }
    // assign new matrix pointer to input
    Matrix M = * pM;
    // walk matrix and free memory
    for(int i = 1; i <= M->n; i++){
        // assign current matrix entry
        List row = M->rows[i];
        // walk thru current matrix row and free entries
        for(moveFront(row); position(row) >= 0; moveNext(row)){
            // assign entry pointer with an entry type cast
            Entry E = (Entry)get(row);
            // free the entry pointer
            free(E);
        }
        // free current matrix entry
        clear(row);
        // free current entry obj
        freeList(&(M->rows[i]));
    }
    // free matrix memory 
    free(M->rows);
    free(M);
    // free matrix pointer
    *pM = NULL;
}

// Access functions -----------------------------------------------------------

// dimension()
// Returns the number of rows and columns of square Matrix M.
int dimension(Matrix M){
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // return matrix dimension
    return M->n;
}
// numNonZero()
// Returns the number of non-zero elements in M.
int numNonZero(Matrix M){
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // return non-zero entries of matrix
    return M->nzn;
}

// equals()
// Returns true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Resets M to the zero Matrix.
// same as freematrix() except keeps the matrix entry objs intact
void makeZero(Matrix M){
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // check for min matrix size
    if(M->n < 1){
        fprintf(stderr, "Matrix too tiny!");
        exit(EXIT_FAILURE);
    }
    // reset matrix values
    M->nzn = 0;
    // reset matrix rows
    for(int i = 1; i <= M->n; i++){
        // assign current matrix entry
        List row = M->rows[i];
        // walk thru current matrix row and free entries
        for(moveFront(row); position(row) >= 0; moveNext(row)){
            // assign entry pointer with an entry type cast
            Entry E = (Entry)get(row);
            // free the entry pointer
            free(E);
        }
        // free current matrix entry
        clear(row);
    }
}

// changeEntry()
// Changes the ith row, jth column of M to be the value x.
// Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x){
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // check for valid row
    if(i < 1 || i > dimension(M)){
        fprintf(stderr, "Invalid row!\n");
        exit(EXIT_FAILURE);
    }
    // check  for valid column
    if(j < 1 || j > dimension(M)){
        fprintf(stderr, "Invalid column!\n");
        exit(EXIT_FAILURE);
    }
    // get entry in current row
    List row = M->rows[i];
    // walk current row until column j encountered
    for(moveFront(row); position(row) >= 0; moveNext(row)){
        // assign entry obj pointer
        Entry E = (Entry)get(row);
        // check for correct column
        if(E->col == j){
            // if inserting 0, destroy entry and decrement non-zero entries
            if(x == 0.0){
                free(E);
                delete(row);
                M->nzn--;
            }
            // if inserting non-zero, update entry value(non-zero entries stay the same)
            else{
                E->val = x;
            }
            // exit once insertion complete
            return;
        }
        // check if current column is beyond insertion point
        // if so, exit row navigation and proceed to creation of new entry
        if(E->col > j){
            break;
        }
    }
    // if inserting 0, but column j was not encountered, exit
    if(x == 0.0){
        return;
    }
    // if column j does not currently exist
    Entry E_new = newEntry(j, x);
    // if we are currently in a valid position in the row
    // insert the new entry before the current one which is greater than column j
    if(position(row) >= 0){
        insertBefore(row, E_new);
    }
    // append new entry to back of list if cursor is undefined
    else{
        append(row, E_new);
    }
    // increment non-zero entries
    M->nzn++;
}

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
void printMatrix(FILE* out, Matrix M) {
    // check for valid matrix
    if(M == NULL){
        fprintf(stderr, "NULL Matrix!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru matrix and print each entry in each row
    for(int i = 1; i <= M->n; i++){
        // assign current matrix entry
        List row = M->rows[i]; 
        // check for non-zero row
        if(length(row) > 0){
            // print row #
            fprintf(stdout, "%d: ", i);
            // iterate thru row and print col, val pair
            for(moveFront(row); position(row) >= 0; moveNext(row)){
                Entry E = (Entry)get(row);
                fprintf(stdout, "(%d , %.1f) ", E->col, E->val);
            }
            // print newline
            fprintf(stdout, "\n");
        }
    }
}