//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA6
// ListTest.cpp
// Unit Test file for List ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "List.h"

int main() {
    List A;

    A.moveFront();
    for(int i = 1; i <= 5; i++){
        A.insertAfter(i);
        A.moveNext();
    }

    int len = A.length();

    A.moveFront();
    A.moveNext();
    int prev = A.peekPrev();

    A.moveBack();
    A.movePrev();
    int next = A.peekNext();

    A.insertBefore(99);
    A.insertAfter(77);

    A.eraseBefore();
    A.eraseAfter();

    List B = A;
    bool equalTest = (A == B);

    List C;
    C = A;

    C.clear();
    int lenAfterClear = C.length();

    return 0;
}