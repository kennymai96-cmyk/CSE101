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
#include <math.h>
#include <string.h>
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
    // define tracking vars
    uint64_t data_index_next;
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
    // check if dictionary is legit
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
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if key is legit
    if (k == NULL) {
        fprintf(stderr, "Key is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // generate hash code
    codeType code = hash(k);
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
valType getValue(Dictionary D, keyType k){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if key is legit
    if (k == NULL) {
        fprintf(stderr, "Key is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // generate hash code
    codeType code = hash(k);
    // iterate thru sparse array and probe for available slots
    for(size_t i = 0; i < D->table_size; i++){
        size_t slot = probe(code, D->table_size, i);
        int64_t index = D->table[slot];
        // check if index is empty, if so break
        if(index == TableEmpty){
            break;
        }
        // check if index is deleted, if so continue
        if(index == TableDeleted){
            continue;
        }
        // if index is not empty or deleted
        // check if the hash code equals the code in table
        // check if the input key equals the key in table 
        // return key's value
        if((D->data[index].code == code) && (strcmp(D->data[index].key, k) == 0)){
            return D->data[index].val;
        }
    }
    // if value associated with key not found
    fprintf(stderr,"Key value pair not found!\n");
    exit(EXIT_FAILURE);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Sets D to the empty state.
void clear(Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru sparse array and set to empty
    for(size_t i = 0; i < D->table_size; i++){
        D->table[i] = TableEmpty;
    }
    // reset element vars
    D->data[0].key = DataEmpty;
    D->data[0].val  = 0;
    D->data[0].code = 0;
    // reset insertion index
    D->data_index_next = 1;
    // reset tracking vars
    D->num_pairs = 0;
    D->num_holes = 0;
    D->table_load_factor = 0.0;
    D->data_density = 1.0;
}

// setValue()
// If D contains a pair with key==k, overwrites the associated value with v,
// otherwise inserts the new pair (k, v) into D.
void setValue(Dictionary D, keyType k, valType v){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if key is legit
    if (k == NULL) {
        fprintf(stderr, "Key is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // generate hash code
    codeType code = hash(k);
    // find a slot in table and return index from table
    size_t slot = findSlot(D, k, code);
    int64_t index = D->table[slot];
    // check if index is not empty or deleted, aka exists already
    // if not, overwrite value with input value and return
    if((index != TableEmpty) && (index != TableDeleted)){
        D->data[index].val = v;
        return;
    }
    // check load factor, and expand if necessary
    if(((double)(D->num_pairs + 1) / D->table_size) > TableLoadFactorThreshold){
        expandTable(D);
        // Recompute new slot from new table
        slot = findSlot(D, k, code);
    }
    // check if expansion is needed for new pair
    if(D->data_index_next == D->data_size){
        expandData(D);
    }
    // declare var to hold index of next insertion
    uint64_t idx = D->data_index_next;
    // insert data into next location
    D->data[idx].key = k;
    D->data[idx].val = v;
    D->data[idx].code = code;
    // insert index into sparse table
    D->table[slot] = idx;
    // update tracking vars
    D->data_index_next++;
    D->num_pairs++;
    // update load factor
    D->table_load_factor = (double)D->num_pairs / D->table_size;
    // update data density
    D->data_density = (double)D->num_pairs / (D->num_pairs + D->num_holes);
}

// removeKey()
// Deletes the pair with key==k from D.
// pre: contains(D, k)
void removeKey(Dictionary D, keyType k){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if key is legit
    if (k == NULL) {
        fprintf(stderr, "Key is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // generate hash code
    codeType code = hash(k);
    // iterate thru sparse array and probe for available slots
    for(size_t i = 0; i < D->table_size; i++){
        size_t slot = probe(code, D->table_size, i);
        int64_t index = D->table[slot];
        // check if index is empty, if so break
        if(index == TableEmpty){
            break;
        }
        // check if index is deleted, if so continue
        if(index == TableDeleted){
            continue;
        }
        // if index is not empty or deleted
        // check if the hash code equals the code in table
        // check if the input key equals the key in table 
        // delete the pair from D and update all vars
        if((D->data[index].code == code) && (strcmp(D->data[index].key, k) == 0)){
            D->table[slot] = TableDeleted;
            D->data[index].key = DataDeleted;
            D->num_pairs--;
            D->num_holes++;
            D->data_density = (double)D->num_pairs / (D->num_pairs + D->num_holes);
            D->table_load_factor = (double)D->num_pairs / D->table_size;
            return;
        }
    }
    // if value associated with key not found
    fprintf(stderr,"Key value pair not found!\n");
    exit(EXIT_FAILURE);
}

// Other operations -----------------------------------------------------------

// copy()
// Returns a new Dictionary containing the same key-value pairs as D.
Dictionary copy(Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // allocate memory for copy dictionary
    Dictionary C = malloc(sizeof(struct DictionaryObj));
    if (C == NULL) {
        fprintf(stderr, "Dictionary memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    // copy fields from OG into copy dictionary
    C->table_size = D->table_size;
    C->table_load_factor = D->table_load_factor;
    C->data_size = D->data_size;
    C->data_index_next = D->data_index_next;
    C->num_pairs = D->num_pairs;
    C->num_holes = D->num_holes;
    C->data_density = D->data_density;
    // allocate memory for sparse array and check success
    C->table = calloc(C->table_size, sizeof(int64_t));
    if (C->table == NULL) {
        free(C);
        fprintf(stderr, "Sparse array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru sparse array and insert indices from OG into copy dictionary
    for(size_t i = 0; i < C->table_size; i++){
        C->table[i] = D->table[i];
    }
    // allocate memory for dense array and check success
    C->data = malloc(C->data_size * sizeof(Element));
    if (C->data == NULL) {
        free(C->table);
        free(C);
        fprintf(stderr, "Dense array allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < C->data_size; i++){
        C->data[i].key = D->data[i].key;
        C->data[i].val  = D->data[i].val;
        C->data[i].code = D->data[i].code;
    }
    return C;
}

// equals()
// Returns true if A and B contain the same key-value pairs, and returns false
// otherwise.
bool equals(Dictionary A, Dictionary B){
    // check if both dictionaries are legit
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if each dictionary is the same size
    // if not return false
    if(A->num_pairs != B->num_pairs){
        return false;
    }
    // iterate thru dictionary A and check for non-hole entries
    // if a valid pair is found, check if B contains the key/value
    for(size_t i = 1; i < A->data_index_next; i++){
        if(A->data[i].key != DataDeleted){
            keyType k = A->data[i].key;
            valType v = A->data[i].val;
            if(contains(B, k) == false){
                return false;
            }
            if(getValue(B, k) != v){
                return false;
            }
        }
    }
    // return true if checks are successful
    return true;
}

// printDictionary()
// Prints a string representation of Dictionary D to the FILE pointer out. Each
// key-value pair is printed on its own line in the form "key : value". Pairs
// will appear in the order in which they were inserted into the Dictionary.
void printDictionary(FILE* out, Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru dictionary and check for non-hole entries
    // if a valid pair is found, check if B contains the key/value
    for(size_t i = 1; i < D->data_index_next; i++){
        if(D->data[i].key != DataDeleted){
            keyType k = D->data[i].key;
            valType v = D->data[i].val;
            fprintf(out, "%s : %d\n", k, v);
        }
    }
}

// printDiagnostic()
// Prints a string representation of the internal state of Dictionary D to FILE
// out. First D->data is printed with accompanying parameters, then D->table
// is printed with its accompanying parameters.
void printDiagnostic(FILE* out, Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n\n");
        exit(EXIT_FAILURE);
    }
    fprintf(out, "***print diagnostic*************************\n");
    fprintf(out, "Data:\n");
    // iterate thru data table and print key: value: hash
    for(size_t i = 0; i < D->data_size; i++){
        keyType k = D->data[i].key;
        valType v = D->data[i].val;
        codeType c = D->data[i].code;
        fprintf(out, "%s : %d : %llu\n", k ? k : "(null)", v, c);
    }
    // print tracking vars
    fprintf(out, "numPairs: %d\n", D->num_pairs);
    fprintf(out, "numDeleted: %d\n", D->num_holes);
    fprintf(out, "dataSize: %zu\n", D->data_size);
    fprintf(out, "dataNextIndex: %zu\n", D->data_index_next);
    fprintf(out, "dataDensity: %.6f\n", D->data_density);
    // print sparse array info
    fprintf(out, "Table:\n");
    for(size_t i = 0; i < D->table_size; i++){
        fprintf(out, "%zu : %d\n", i, D->table[i]);
    }
    fprintf(out, "tableSize: %zu\n", D->table_size);
    fprintf(out, "tableLoadFactor: %.6f\n", D->table_load_factor);
    fprintf(out, "********************************************\n");
}

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
uint64_t findSlot(Dictionary D, keyType k, codeType code){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // check if key is legit
    if (k == NULL) {
        fprintf(stderr, "Key is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // init deleted slot tracker
    int64_t del_slot = -1;
    // iterate thru sparse array and probe for available slots
    for(size_t i = 0; i < D->table_size; i++){
        size_t slot = probe(code, D->table_size, i);
        int64_t index = D->table[slot];
        // check if index is empty
        // if a deleted slot has been encountered, return it
        // otherwise return current slot
        if(index == TableEmpty){
            if(del_slot != -1){
                return del_slot;
            }
            return slot;
        }
        // check if index is deleted
        // check if del slot has been encountered
        // if not set current slot as del slot and continue
        if(index == TableDeleted){
            if(del_slot == -1){
                del_slot = slot;
            }
            continue;
        }
        // if index is not empty or deleted
        // check if the hash code equals the code in table
        // check if the input key equals the key in table 
        if((D->data[index].code == code) && (strcmp(D->data[index].key, k) == 0)){
            return slot;
        }
    }
}

// insertIndex()
// Steps through the probe sequence for code and inserts idx into the first
// slot in array T (of length m) at which either the special value TableEmpty
// or the special value TableDeleted are found.
void insertIndex(int64_t* T, size_t m, size_t idx, codeType code){
    // iterate thru new sparse array
    for(size_t i = 0; i < m; i++){
        size_t slot = probe(code, m, i);
        // check if index is empty or deleted
        // assign current slot with inputted index
        if((T[slot] == TableEmpty) || (T[slot] == TableDeleted)){
            T[slot] = idx;
            return;
        }
    }
    // if no insertion takes place
    fprintf(stderr, "No valid insertion target!");
    exit(EXIT_FAILURE);
}

// expandTable()
// Expands length of array D->table. If tableSize<TableSizeThreshold, increases
// size by TableExpandFactor1, otherwise increases size by TableExpandFactor2.
// Re-inserts indices of D->data into D->table.
void expandTable(Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // compact data if eligible
    if(D->data_density < DataDensityThreshold){
        compactData(D);
    }
    // init new sparse array size var
    size_t size_new = 0;
    // check which expansion factor to use
    if(D->table_size < TableSizeThreshold){
        size_new = D->table_size * TableExpandFactor1;
    }
    else{
        size_new = D->table_size * TableExpandFactor2;
    }
    // allocate memory for new sparse array
    int64_t* T_new = calloc(size_new, sizeof(int64_t));
    if (T_new == NULL) {
        fprintf(stderr, "Table expansion failed!\n");
        exit(EXIT_FAILURE);
    }
    // iterate thru new sparse array and re-insert indices
    for(size_t i = 1; i < D->data_index_next; i++){
        if(D->data[i].key != DataDeleted){
            insertIndex(T_new, size_new, i, D->data[i].code);
        }
    }
    // free old table
    free(D->table);
    // assign new table vars
    D->table = T_new;
    D->table_size = size_new;
    // calc load factor
    D->table_load_factor = (double)D->num_pairs / D->table_size;
}

// expandData()
// Expands length of array D->data, leaving contents unchanged.
void expandData(Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // init new dense array size var
    uint64_t size_new = 0; 
    size_new = ceil((D->data_size * DataExpandFactor));
    // allocate memory for new dense array
    Element* D_new = realloc(D->data, size_new * sizeof(Element));
    if(D_new == NULL){
        fprintf(stderr, "Data expansion failed\n");
        exit(EXIT_FAILURE);
    }
    // assign new data vars
    D->data = D_new;
    D->data_size = size_new;
}

// compactData()
// Removes the deleted elements from array D->data, making its entries contiguous,
// and sets D->dataDensity equal to 1.
void compactData(Dictionary D){
    // check if dictionary is legit
    if (D == NULL) {
        fprintf(stderr, "Dictionary is NULL!\n");
        exit(EXIT_FAILURE);
    }
    // declare var to track new indices
    uint64_t new = 1;
    // iterate thru dense array and check for holes
    // if key is not a hole, update current index with old index's key
    // increment new index and repeat check for holes
    for(size_t old = 1; old < D->data_index_next; old++){
        if(D->data[old].key != DataDeleted){
            if(new != old){
                D->data[new] = D->data[old];
            }
            new++;
        }
    }
    // update tracking vars
    D->data_index_next = new;
    D->num_holes = 0;
    D->data_density = 1.0;
}
