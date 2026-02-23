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

// Constructors --------------------------------------------------------

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
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    // TODO
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    // TODO
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    // TODO
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    // TODO
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    // TODO
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    // TODO
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    // TODO
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    // TODO
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    // TODO
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    // TODO
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    // TODO
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    // TODO
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    // TODO
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    // TODO
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    // TODO
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    // TODO
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    // TODO
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    // TODO
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    // TODO
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // TODO
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    // TODO
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    // TODO
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    // TODO
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    // TODO
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    // TODO
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    // TODO
}