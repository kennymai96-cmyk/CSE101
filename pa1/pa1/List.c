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

// test-only helper function: builds a 2-element list
List makeTestList(ListElement data1, ListElement data2) {
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);

    Node N1 = newNode(data1);
    Node N2 = newNode(data2);

    N1->prev = NULL; // link and cap list on front/back
    N1->next = N2;
    N2->prev = N1;
    N2->next = NULL;

    L->front  = N1; // N1 at front
    L->back   = N2; // N2 at back
    L->length = 2; // 2 elements in list
    L->cursor = N1; // init to NULL

    return L;
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
    while(length(*pL) > 0){ // iterate thru list pointer and free memory
        deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
}

// Access functions 

int length(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }
    return L->length; // return list length
}

// position()
// If cursor is defined, returns the position of the cursor element, otherwise
// returns -1.
int position(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }


    if((L->cursor != NULL) && (L->pos != -1)) { // check if cursor defined 
        return L->pos; // return cursor position
    }
    else {
        return -1;
    }
}

// front()
// Returns front element. Pre: length()>0
ListElement front(List L) {
    if(L == NULL) {
        fprintf(stderr, "NULL List!\n"); // check that list exists
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Empty List!\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data; // grab data from the front list item
}

// back()
// Returns back element.
// Pre: length(L)>0
ListElement back(List L) {
    if(L == NULL) {
        fprintf(stderr, "NULL List!\n"); // check that list exists
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Empty List!\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data; // grab data from the back list item
}

// get()
// Returns cursor element.
// Pre: length(L)>0, position(L)>=0
ListElement get(List L) {
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == NULL) { // check is cursor is NULL
         fprintf(stderr, "Cursor is NULL!\n");
        exit(EXIT_FAILURE);       
    }

    return L->cursor->data; // return data at cursor position
}

// equals()
// Returns true if A and B are the same integer sequence, false otherwise.
// The cursor is not altered in either List.
bool equals(List A, List B){
    if(A == NULL || B == NULL) { // check that lists exist
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if (length(A) != length(B)) {
        return false; // return false if no match in length
    }

    Node one = A->front; // point to front of Node A
    Node two = B->front; // point to front of Node B

    while (one != NULL) { // return true if match
        if(one->data != two->data) {
            return false; // return false if no match in data
        }
        one = one->next;
        two = two->next;
    }

    return true;
}

// Manipulation procedures 

// clear()
// Resets L to its original empty state.
void clear(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    while (length(L) > 0) {
        deleteFront(L);
    }

    L->pos = -1; // set cursor position as undefined
    L->cursor = NULL; // deinit cursor
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length(L)>0, position(L)>=0
void set(List L, ListElement x){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

     if((length(L) <= 0) || (position(L) < 0)) { // check for valid length and position
        fprintf(stderr, "Length or position invalid!\n");
        exit(EXIT_FAILURE);
    }   

    L->cursor->data = x; // overwrite cursor element's data
}

// moveFront()
// If L is non-empty, places the cursor under the front element, otherwise does
// nothing.
void moveFront(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(length(L) > 0) { // check that there are elements
        L->pos = 0; // set cursor position to front
        L->cursor = L->front; // set cursor to front Node
    }
}

// moveBack()
// If L is non-empty, places the cursor under the back element, otherwise does
// nothing.
void moveBack(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(length(L) > 0) { // check that there are elements
        L->pos = (length(L) - 1); // set cursor position to back
        L->cursor = L->back; // set cursor to front Node
    }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward front of
// L. If cursor is defined and at front, cursor becomes undefined.
// If cursor is undefined does nothing.
void movePrev(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if((L->cursor != NULL) && (L->pos != -1) && (L->cursor != L->front)) { // check if cursor defined and not at front
        L->pos -= 1; // decrement position towards front
        L-> cursor = L->cursor->prev; // set cursor to prev Node
    }

    else if((L->cursor != NULL) && (L->pos != -1) && (L->cursor == L->front)) { // check if cursor defined and at front)
        L-> pos = -1; // set cursor position to undefined
        L->cursor = NULL; // deinit cursor
    }
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward back of
// L. If cursor is defined and at back, cursor becomes undefined.
// If cursor is undefined does nothing.
void moveNext(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if((L->cursor != NULL) && (L->pos != -1) && (L->cursor != L->back)) { // check if cursor defined and not at back
        L->pos += 1; // decrement position towards back
        L-> cursor = L->cursor->next; // set cursor to next Node
    }

    else if((L->cursor != NULL) && (L->pos != -1) && (L->cursor == L->back)) { // check if cursor defined and at back)
        L-> pos = -1; // set cursor position to undefined
        L->cursor = NULL; // deinit cursor
    }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place
// before front element.
void prepend(List L, ListElement data){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(length(L)== 0) { // check if list is empty
        Node N = newNode(data); // define new Node with inputted data
        N->prev = NULL; // cap left side of new Node 
        N->next = NULL; // cap right side of new Node    
        L->front = L->back = N; // set new Node as front
        L->length += 1; // increase list size by 1
        if(L->cursor != NULL) {
            L->pos += 1; // increment cursor position by 1
        }
    }

    else if(length(L) > 0) { // check that there are elements
        Node N = newNode(data); // define new Node with inputted data
        N->next = L->front; // connect new Node to prior front
        N->prev = NULL; // cap left side of new Node
        L->front->prev = N; // connect old front left side to new Node
        L->front = N; // set new Node as front
        L->length += 1; // increase list size by 1
        if(L->cursor != NULL) {
            L->pos += 1; // increment cursor position by 1
        }
    }
}

// append()
// Insert new element into L. If List is non-empty, insertion takes place
// after back element.
void append(List L, ListElement data){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(length(L)== 0) { // check if list is empty
        Node N = newNode(data); // define new Node with inputted data
        N->prev = NULL; // cap left side of new Node 
        N->next = NULL; // cap right side of new Node    
        L->front = L->back = N; // set new Node as front
        L->length += 1; // increase list size by 1
    }

    else if(length(L) > 0) { // check that there are elements
        Node N = newNode(data); // define new Node with inputted data
        N->prev = L->back; // connect new Node to prior back
        N->next = NULL; // cap right side of new Node
        L->back->next = N; // connect old back right side to new Node
        L->back = N; // set new Node as front
        L->length += 1; // increase list size by 1
    }
}

// insertBefore()
// Insert new element before cursor.
// Pre: length(L)>0, position(L)>=0
void insertBefore(List L, ListElement data){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if((length(L) <= 0) || (position(L) < 0)) { // check for valid length and position
        fprintf(stderr, "Length or position invalid!\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->front) { // check for front case
        Node N = newNode(data); // define new Node with inputted data
        N->prev = L->cursor->prev; // cap new Node's left
        N->next = L->cursor; // link new Node next to cursor
        L->cursor->prev = N; // link cursor Node prev to new Node
        L->length += 1; // increase list size by 1
        L->front = N; // set new Node as front
        if(L->cursor != NULL) {
            L->pos += 1; // increment cursor position by 1
        }  
    }

    else { // handle non-front case
        Node N = newNode(data); // define new Node with inputted data
        N->prev = L->cursor->prev; // link new Node prev to cursor Node's prev
        N->next = L->cursor; // link new Node next to cursor
        L->cursor->prev->next = N; // link new Node to adjacent cursor node
        L->cursor->prev = N; // link cursor Node prev to new Node
        L->length += 1; // increase list size by 1
        if(L->cursor != NULL) {
            L->pos += 1; // increment cursor position by 1
        }  
    }
}

// insertAfter()
// Inserts new element after cursor.
// Pre: length(L)>0, position(L)>=0
void insertAfter(List L, ListElement data){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if((length(L) <= 0) || (position(L) < 0)) { // check for valid length and position
        fprintf(stderr, "Length or position invalid!\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->back) { // check for back case
        Node N = newNode(data); // define new Node with inputted data
        N->prev = L->cursor; // link new Node prev to cursor
        N->next = NULL; // cap new Node's right
        L->cursor->next = N; // link cursor Node next to new Node
        L->length += 1; // increase list size by 1
        L->back = N; // set new Node as back
    }

    else { // handle non-back case
        Node N = newNode(data); // define new Node with inputted data
        N->prev = L->cursor; // link new Node prev to cursor
        N->next = L->cursor->next; // link new Node next to cursor Node's next
        L->cursor->next->prev = N; // link new Node to adjacent cursor node
        L->cursor->next = N; // set cursor node's next to new Node
        L->length += 1; // increase list size by 1
    }
}

// deleteFront()
// Deletes the front element.
// Pre: length(L)>0
void deleteFront(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Cannot delete empty list!\n");
        exit(EXIT_FAILURE);        
    }

    Node N = L->front; // sequester front Node

    if(L->cursor == N){
        L->cursor = NULL;
        L->pos = -1;
    }
    else if(L->pos != -1){
        L->pos--;
    }

    if(L->length == 1) { // check for list length of 1
        L->front = NULL; // deinit front pointer
        L->back = NULL; // deinit back pointer
        L->length = 0; // set list length to 0
        free(N); // free memory
    }
    else {
        L->front = N->next; // make next Node the new front
        L->front->prev = NULL; // make prior Node pointer null
        L->length--; // decerement length
        free(N); // free memory
    }
}

// deleteBack()
// Deletes the back element.
// Pre: length(L)>0
void deleteBack(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Cannot delete empty list!\n");
        exit(EXIT_FAILURE);        
    }

    Node N = L->back; // sequester back Node

    if(L->cursor == N){
        L->cursor = NULL;
        L->pos = -1;
    }

    if(L->length == 1) { // check for list length of 1
        L->front = NULL; // deinit front pointer
        L->back = NULL; // deinit back pointer
        L->length = 0; // set list length to 0
        free(N); // free memory
    }
    else{
        L->back = N->prev; // make next Node the new back
        L->back->next = NULL; // make prior Node pointer null
        L->length--; // decerement length
        free(N); // free memory
    }
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length(L)>0, position(L)>=0
void delete(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Cannot delete empty list!\n");
        exit(EXIT_FAILURE);        
    }

    if(L->pos < 0 || L->cursor == NULL) {
        fprintf(stderr, "Cursor position is undefined!\n");
        exit(EXIT_FAILURE);  
    }

    Node N = L->cursor; // sequester cursor Node

    if(L->length == 1) { // check for list length of 1
        L->front = NULL; // deinit front pointer
        L->back = NULL; // deinit back pointer
        L->cursor =  NULL; //deinit cursor
    }
    else if(N == L->front) {
        L->front = N->next; // relink front
        L->front->prev = NULL; // deinit prev pointer
    }
    else if(N == L->back) {
        L->back = N->prev; // relink back
        L->back->next = NULL; // deinit next pointer
    }
    else {
        N->next->prev = N->prev;
        N->prev->next = N->next;
    }

    L-> length--; // decrement length
    L->cursor = NULL; // deinit cursor 
    L->pos = -1; // set cursor position as undefined
    free(N); // free memory
}

// Other operations 

// printList()
// Prints a string representation of L consisting of a comma separated sequence
// of integers, surrounded by parentheses, with front on left, to the stream
// pointed to by out.
void printList(FILE* out, List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "("); // opening (

    Node N = L->front; // temp Node set to front of List

    while(N != NULL) { // iterate and copy list elements to output file until end of List
        fprintf(out, "%d", N-> data);
        if(N->next != NULL) {
            fprintf(out, ", ");
        }
        N = N->next;
    }

    fprintf(out, ")\n"); // closing )
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The List L is unchanged.
List copyList(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    List L_new = newList(); // create new empty list

    if(length(L) == 0) { // check for length of 0
        return L_new; // return new List as empty
    }

    Node N = L->front; // set temp Node as front of og List

    while (N != NULL) { // iterate thru and append og List elements to new List
        append(L_new, N->data);
        N = N->next;
    }

    return L_new;
}

// join()
// Returns the concatenation of A followed by B.
// The cursor in the new List is undefined, regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List join(List A, List B){
    if((A == NULL) || (B == NULL)) { // check that both lists exist
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    List L_new = newList(); // create new empty list

    int total_l = length(A) + length(B);
    if (total_l == 0) {
        return L_new; 
    }

    Node N = A->front; // set temp Node as front of List A

    while (N != NULL) { // iterate thru and append List A elements to new List
        append(L_new, N->data);
        N = N->next;
    }

    Node N2 = B->front; // set temp Node as front of List B

    while (N2 != NULL) { // iterate thru and append List B elements to new List
        append(L_new, N2->data);
        N2 = N2->next;
    }

    return L_new;   
}

// split()
// Removes all elements before (in front of but not equal to) the cursor element in L.
// The cursor element in L is unchanged.
// Returns a new List consisting of all the removed elements.
// The cursor in the returned list is undefined.
// Pre: length(L)>0, position(L)>=0
List split(List L){
    if(L == NULL) { // check that list exists
        fprintf(stderr, "NULL List!\n");
        exit(EXIT_FAILURE);
    }

    if(L->length == 0) { // check for empty list
        fprintf(stderr, "Cannot delete empty list!\n");
        exit(EXIT_FAILURE);        
    }

    if(L->pos < 0 || L->cursor == NULL) {
        fprintf(stderr, "Cursor position is undefined!\n");
        exit(EXIT_FAILURE);  
    }

    List L_new = newList(); // create new empty list 

    while (L->front != L->cursor) { // iterate thru og List and delete/append until cursor is hit
        append(L_new, L->front->data);
        deleteFront(L); 
    }

    return L_new; 
}
