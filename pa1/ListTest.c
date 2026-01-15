//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA1
// ListTest.c
// Unit Tests for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

int main(void){

    List A = newList();
    List B = newList();

    // test append
    for(int i = 1; i <= 10; i++){
        append(A, i);
        append(B, i);
    }

    // test equals
    assert(equals(A, B));

    // test moveFront and get
    moveFront(A);
    assert(get(A) == 1);

    // test moveNext
    moveNext(A);
    assert(get(A) == 2);

    // test insertBefore
    insertBefore(A, 99);
    moveFront(A);
    assert(get(A) == 99);

    // test deleteFront
    deleteFront(A);
    moveFront(A);
    assert(get(A) == 1);

    // test moveBack and insertAfter
    moveBack(A);
    insertAfter(A, 100);
    moveBack(A);
    assert(get(A) == 100);

    // test deleteBack
    deleteBack(A);
    moveBack(A);
    assert(get(A) == 10);

    // test clear
    clear(A);
    assert(length(A) == 0);

    // cleanup
    freeList(&A);
    freeList(&B);

    printf("All List tests passed.\n");
    return 0;
}
