//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA6
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// Class Constructors & Destructors -----------------------------

// Node constructor 
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// List constructor
List::List(){
    // define dummy nodes
    frontDummy = new Node(0);
    backDummy = new Node(0);
    // link dummies together
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    // init cursors 
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    // init list tracking vars
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor
List::List(const List& L){
    // define dummy nodes
    frontDummy = new Node(0);
    backDummy = new Node(0);
    // link dummies together
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    // init cursors 
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    // init list tracking vars
    pos_cursor = 0;
    num_elements = 0;
    // declare node pointer to reference elements
    Node* N = L.frontDummy->next;
    // iterate thru list until backDummy is encountered
    // insert elements 
    while(N != L.backDummy){
        insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    // match new list's cursor to old list
    moveFront();
    for(int i = 0; i < L.pos_cursor; i++){
        moveNext();
    }
}

// Destructor
List::~List(){
    // declare node pointer to reference elements
    Node* N = frontDummy->next;
    // iterate thru list until backDummy is encountered
    // point to next node and delete current one
    while(N != backDummy){
        Node* next = N->next;
        delete N;
        N = next;
    }
    // delete dummies
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    // return number of elements
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if(length() <= 0){
        throw std::length_error("Empty List!");
    }
    // can't use cursor because const stops modification
    // return the first element
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if(length() <= 0){
        throw std::length_error("Empty List!");
    }
    // can't use cursor because const stops modification
    // return the last element
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if(pos_cursor >= length()){
        throw std::length_error("At end of List!");
    }
    // can't use cursor because const stops modification
    // return element after cursor
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if(pos_cursor >= length()){
        throw std::length_error("At end of List!");
    }
    // can't use cursor because const stops modification
    // return element after cursor
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    // declare node pointer to reference elements
    Node* N = frontDummy->next;
    // iterate thru list until backDummy is encountered
    // point to next node and delete current one
    while(N != backDummy){
        Node* next = N->next;
        delete N;
        N = next;
    }
    // reconnect dummies
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    // reset cursor
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    // reset tracking vars
    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    // move cursor to front
    pos_cursor = 0;
    // reset cursor
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    // move cursor to back
    pos_cursor = length();
    // reset cursor
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    // check if cursor is already at the back of list
    if(position() >= length()){
        throw std::length_error("Cursor at the back!");
    }
    // set element to next node
    ListElement x = afterCursor->data;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    // move cursor to next node
    pos_cursor++;
    // return list element
    return x;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    // check if cursor is already at the front of list
    if(position() <= 0){
        throw std::length_error("Cursor at the front!");
    }
    // set element to prev node
    ListElement x = beforeCursor->data;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    // move cursor to prev node
    pos_cursor--;
    // return list element
    return x;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    // create new node and link its cursors
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    // reorient before/after cursors
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    // increment num of elements in list
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    // create new node and link its cursors
    Node* N = new Node(x);
    N->prev = beforeCursor;
    N->next = afterCursor;
    // reorient before/after cursors
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    // increment cursor
    pos_cursor++;
    // increment num of elements in list
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    // check if cursor is already at the back of list
    if(position() >= length()){
        throw std::length_error("Cursor at the back!");
    }
    // update next node with x
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    // check if cursor is already at the front of list
    if(position() <= 0){
        throw std::length_error("Cursor at the front!");
    }
    // update prev node with x
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    // check if cursor is already at the back of list
    if(position() >= length()){
        throw std::length_error("Cursor at the back!");
    }
    // assign node for deletion
    Node* del = afterCursor;
    // save temp node for later relink
    Node* next = afterCursor->next;
    // reorient cursors
    beforeCursor->next = next;
    afterCursor = next;
    // link new node
    next->prev = beforeCursor;
    // delete node
    delete del;
    // decrement num of elements in list
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    // check if cursor is already at the front of list
    if(position() <= 0){
        throw std::length_error("Cursor at the front!");
    }
    // assign node for deletion
    Node* del = beforeCursor;
    // save temp node for later relink
    Node* prev = beforeCursor->prev;
    // reorient cursors
    beforeCursor = prev;
    afterCursor->prev = prev;
    // link new node
    prev->next = afterCursor;
    // delete node
    delete del;
    // decrement num of elements in list
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    // iterate thru list from current cursor until backDummy is encountered
    // move cursor after found element
    // return cursor position if element is found
    while(afterCursor != backDummy){
        if(afterCursor->data == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    // return -1 if x not found
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    // iterate thru list from current cursor until frontDummy is encountered
    // move cursor before found element
    // return cursor position if element is found
    while(beforeCursor != frontDummy){
        if(beforeCursor->data == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    // return -1 if x not found
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // declare node pointer to reference elements
    Node* N = frontDummy->next;
    // iterate thru list examining current node until backDummy is encountered
    while(N != backDummy){
        // assign temp node to examine next node in line
        Node* next = N->next;
        // iterate thru list examining next node until backDummy is encountered
        // if data from current and next node match, delete current node and relink nodes
        // if no match, continue examining 
        while(next != backDummy){
            if(N->data == next->data){
                Node* del = next;
                next = next->next;
                // adjust cursor if they point to node being delted
                if (del == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                    pos_cursor--;
                }
                if (del == afterCursor) {
                    afterCursor = afterCursor->next;
                }
                del->prev->next = del->next;
                del->next->prev = del->prev;
                // delete node
                delete del;
                // decrement num of elements in list
                num_elements--;
            }
            else{
                next = next->next;
            }
        }
    N = N->next;
    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    // create new empty list
    List cat;
    // assign node for traversal
    Node* N = frontDummy->next;
    // iterate until backdummy is hit for the calling list
    while(N != backDummy){
        cat.insertAfter(N->data);
        N = N->next;
    }
    // iterate until backdummy is hit for the argument list
    Node* N2 = L.frontDummy->next;
    while(N2 != L.backDummy){
        cat.insertAfter(N2->data);
        N2 = N2->next;
    }
    // move cursor in new list to front
    cat.moveFront();
    // return new list
    return cat;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    // assign node for traversal
    Node* N = frontDummy->next;
    // declare string to hold output
    std::string s = "(";
    // iterate thru list until backdummy is hit
    // add list element to output string
    // keep printing separation commas as long as you are not at end of list
    while(N != backDummy){
        s += std::to_string(N->data);
        if(N->next != backDummy){
            s += ", ";
        }
        N = N->next;
    }
    s += ")";
    // return final string
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    // check for equal lengths
    if(length() != R.length()){
        return false;
    }
    // assign temp nodes for traversal
    Node* N = frontDummy->next;
    Node* N2 = R.frontDummy->next;
    // iterate thru each list until backdummy is hit
    while(N != backDummy){
        if(N->data != N2->data){
            return false;
        }
        N = N->next;
        N2 = N2->next;
    }
    // return true if loop completes successfully
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    // assign node for traversal
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    // check if both pointers are the same
    // if not clear this list
    // iterate thru list with temp node and insert contents into this list
    if(this != &L){
        this->clear();
        Node* N = frontDummy->next;
        while(N != backDummy){
            this->insertAfter(N->data);
            this->moveNext();
            N = N->next;
        }
    }
    // return list pointer
    return *this;
}