//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA5
// Dictionary.c
// ImpMementation file for Dictionary ADT
//-----------------------------------------------------------------------------

#include <stdio.h> // required libraries
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include "Dictionary.h"

// alias for uint64
typedef uint64_t codeType;

// Constants for table array (sparse, indices to data array)
const size_t TableInitialSize = 8;
const double TableLoadFactorThreshold = 0.67;
const int TableExpandFactor1 = 4;
const int TableExpandFactor2 = 2;
const int TableSizeThreshold = 50000;
const int TableEmpty = 0;
const int TableDeleted = -1;

// Constants for data array (dense, dictionary data)
const size_t DataInitialSize = 1;
const double DataExpandFactor = 1.5;
const double DataDensityThreshold = 0.8;
const keyType DataEmpty = NULL;
const char dummy[] = {255, 0}; // array is const
const keyType DataDeleted = dummy; // pointer is const

// define triple type contained in dense array
typedef struct Element{
    keyType key;
    valType val;
    codeType code;
} Element;

// define DictionaryObh
struct DictionaryObj{
    // define sparse array hash table
    // runs hash function on key to determine look up/insertion location
    int64_t* table;
    size_t table_size;
    double table_load_factor;
    // define dense array
    // contains (key, value, code)
    Element* data;
    uint64_t data_size;
    uint64_t data_index_next;
    // define tracking vars
    uint64_t num_pairs;
    uint64_t num_holes;
    double data_density;
};

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructs a new empty Dictionary.
Dictionary newDictionary(void){
    // allocate memory for Dictionary and check success
    Dictionary D = malloc(sizeof(struct DictionaryObj));
    if (D == NULL) {
        fprintf(stderr, "Dictionary memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    // allocate memory for sparse array and check success
    D->table = calloc(TableInitialSize, sizeof(int64_t));
    if (D->table == NULL) {
        free(D);
        fprintf(stderr, "Sparse array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    // allocate memory for dense array and check success
    D->data = malloc(DataInitialSize * sizeof(Element));
    if (D->data == NULL) {
        free(D->table);
        free(D);
        fprintf(stderr, "Dense array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    // init element vars
    D->data[0].key = DataEmpty;
    D->data[0].val  = 0;
    D->data[0].code = 0;
    // init sparse array vars
    D->table_size = TableInitialSize;
    D->table_load_factor = 0.0;
    // init dense array vars
    D->data_size = DataInitialSize;
    D->data_index_next = 1;
    // init tracking vars
    D->num_pairs = 0;
    D->num_holes = 0;
    D->data_density = 1.0;
    // return new Dictionary
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, and sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    // check for valid dictionary pointer
    if(pD == NULL || *pD == NULL){
        fprintf(stderr, "NULL dictionary pointer!\n");
        exit(EXIT_FAILURE);
    }
    // assign dictionaryobj pointer to input
    Dictionary D = *pD;
    // free both arrays and dictionary itself
    free(D->table);
    free(D->data);
    free(D);
    // free dictionary pointer
    *pD = NULL;
}

// Access functions -----------------------------------------------------------

// size()
// Returns the number of key-value pairs in D.
int size(Dictionary D){
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // return num of key-value pairs
    return D->num_pairs;
}

// contains()
// Returns true if D contains a pair with key k, returns false otherwise.
bool contains(Dictionary D, keyType k){
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // generate hash code
    codeType code = hash(k);
    // check if hash code is legit
    if (k == NULL) {
        fprintf(stderr, "Hash code is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru sparse array and probe for available slots
    for(size_t i = 0; i < D->table_size; i++){
        size_t slot = probe(code, D->table_size, i);
        int64_t index = D->table[slot];
        // check if index is empty, if so return false
        if(index == TableEmpty){
            return false;
        }
        // check if index is deleted, if so continue
        if(index == TableDeleted){
            continue;
        }
        // if index is not empty or deleted
        // check if the hash code equals the code in table
        // check if the input key equals the key in table 
        if((D->data[index].code == code) && (strcmp(D->data[index].key, k) == 0)){
            return true;
        }
    }
    // catch-all if no match found
    return false;
}

// getValue()
// Returns the value associated with key k.
// pre: contains(D, k)
valType getValue(Dictionary D, keyType k);

// Manipulation procedures ----------------------------------------------------

// clear()
// Sets D to the empty state.
void clear(Dictionary D);

// setValue()
// If D contains a pair with key==k, overwrites the associated value with v,
// otherwise inserts the new pair (k, v) into D.
void setValue(Dictionary D, keyType k, valType v);

// removeKey()
// Deletes the pair with key==k from D.
// pre: contains(D, k)
void removeKey(Dictionary D, keyType k);

// Other operations -----------------------------------------------------------

// copy()
// Returns a new Dictionary containing the same key-value pairs as D.
Dictionary copy(Dictionary D);

// equals()
// Returns true if A and B contain the same key-value pairs, and returns false
// otherwise.
bool equals(Dictionary A, Dictionary B);

// printDictionary()
// Prints a string representation of Dictionary D to the FILE pointer out. Each
// key-value pair is printed on its own line in the form "key : value". Pairs
// will appear in the order in which they were inserted into the Dictionary.
void printDictionary(FILE* out, Dictionary D);

// printDiagnostic()
// Prints a string representation of the internal state of Dictionary D to FILE
// out. First D->data is printed with accompanying parameters, then D->table
// is printed with its accompanying parameters.
void printDiagnostic(FILE* out, Dictionary D);

// Required Helper functions ---------------------------------------------------

// hash()
// Returns the hash code for key k.
codeType hash(keyType k) {
 codeType magicNumber1 = 0xcbf29ce484222325;
 codeType magicNumber2 = 0x100000001b3;
 codeType result = magicNumber1;
 codeType nextChar = *k; // get 1st char in k
 while( nextChar ) { // while not at end of k
 result ^= nextChar; // result = result (exor) nextChar
 result *= magicNumber2; // result = result * magicNumber2
 nextChar = *(++k); // get next char
 }
 return result;
}

// probe()
// Returns the ith term in the probe sequence for code.
size_t probe(codeType code, size_t tbl_size, size_t i){
 codeType h1 = code & (tbl_size-1); // code % tbl_size
 codeType h2 = 2*(code & (tbl_size/2 - 1)) + 1; // 2*(code % tbl_size/2) + 1
 return (h1 + i*h2) & (tbl_size-1); // (h1 + i*h2) % tbl_size
}

// Optional Helper functions ---------------------------------------------------

// findSlot()
// Steps through the probe sequence for code=hash(k). If the Dictionary contains
// key k, returns the slot in D->table containing the index of key k in D->data.
// Otherwise, returns the first slot in D->table that contains either the special
// value TableEmpty or the special value TableDeleted.
uint64_t findSlot(Dictionary D, keyType k, codeType code);

// insertIndex()
// Steps through the probe sequence for code and inserts idx into the first
// slot in array T (of length m) at which either the special value TableEmpty
// or the special value TableDeleted are found.
void insertIndex(int64_t* T, size_t m, size_t idx, codeType code);

// expandTable()
// Expands length of array D->table. If tableSize<TableSizeThreshold, increases
// size by TableExpandFactor1, otherwise increases size by TableExpandFactor2.
// Re-inserts indices of D->data into D->table.
void expandTable(Dictionary D);

// expandData()
// Expands length of array D->data, leaving contents unchanged.
void expandData(Dictionary D);

// compactData()
// Removes the deleted elements from array D->data, making its entries contiguious,
// and sets D->dataDensity equal to 1.
void compactData(Dictionary D);
