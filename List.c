//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA1
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h> // required libraries
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// Defines private Node Type(bi-directional w/ int data type)
typedef struct NodeObj{
    ListElement data; // contains word
    struct NodeObj* prev; // pointer to prev Node
    struct NodeObj* next; // pointer to next Node
} NodeObj; //alias

typedef NodeObj* Node; // defines pointer to NodeObj

// private ListObj type 
typedef struct ListObj{
    Node front; // pointer to Node at position 0
    Node back; // pointer to Node at position n - 1
    Node cursor; // pointer to the current Node, NULL if undefined 
    int length; // number of elements in the list
    int pos; // cursor position, -1 if undefined
} ListObj;

// defines opaque Node constructor for easier node creation
static Node newNode(ListElement data){
    Node N = malloc(sizeof(NodeObj)); // allocate memory for a new Node
    assert(N != NULL); // if malloc fails, blow up program
    N->data = data; // pass int data to new Node
    N->prev = NULL; // initialize prev pointer
    N->next = NULL; // initialize next pointer
    return N; // return Node
}

// Constructors-Destructors 

// newList()
// Creates a new empty list.
List newList(void){
    List L = malloc(sizeof(ListObj)); // allocate memory for a new List
    assert(L != NULL); // if malloc fails, blow up program
    L->front = NULL; // initialize front Node pointer
    L->back = NULL;  // initialize back Node pointer
    L->cursor = NULL; // initizalize current node pointer
    L->length = 0; // initialize list length int
    L->pos = -1; // initialize cursor position as default undefined
    return L; // return List
}

// freeList()
// Frees heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL){
    if(pL != NULL && *pL != NULL) { // check for NULL condition on the address and content of 
        while(!isEmpty(*pL)) {
            delete(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions 

int length(List L){
    
    return 0;
}

int position(List L){
    return -1;
}

ListElement front(List L){
    return 0;
}

ListElement back(List L){
    return 0;
}

ListElement get(List L){
    return 0;
}

bool equals(List A, List B){
    return false;
}

// Manipulation procedures 

void clear(List L){
}

void set(List L, ListElement x){
}

void moveFront(List L){
}

void moveBack(List L){
}

void movePrev(List L){
}

void moveNext(List L){
}

void prepend(List L, ListElement data){
}

void append(List L, ListElement data){
}

void insertBefore(List L, ListElement data){
}

void insertAfter(List L, ListElement data){
}

void deleteFront(List L){
}

void deleteBack(List L){
}

void delete(List L){
}

// Other operations 

void printList(FILE* out, List L){
}

List copyList(List L){
    return NULL;
}

List join(List A, List B){
    return NULL;
}

List split(List L){
    return NULL;
}
