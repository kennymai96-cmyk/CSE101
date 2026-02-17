//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA1
// ListTest.c
// Self-created Unit Tests for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

int main(void){

    printf("=== List ADT Tests ===\n\n");

    // Test 1: newList(), length()
    List L = newList();
    assert(L != NULL);
    assert(length(L) == 0);
    printf("Test 1 passed: newList()\n");

    // Test 2: append(), front(), back()
    append(L, 10);
    append(L, 20);
    append(L, 30);
    assert(length(L) == 3);
    assert(front(L) == 10);
    assert(back(L) == 30);
    printf("Test 2 passed: append/front/back\n");

    // Test 3: moveFront(), get(), position()
    moveFront(L);
    assert(position(L) == 0);
    assert(get(L) == 10);
    printf("Test 3 passed: moveFront/get/position\n");

    // Test 4: moveNext(), moveBack()
    moveNext(L);
    assert(position(L) == 1);
    assert(get(L) == 20);
    moveBack(L);
    assert(position(L) == 2);
    assert(get(L) == 30);
    printf("Test 4 passed: moveNext/moveBack\n");

    // Test 5: insertBefore(), insertAfter()
    insertBefore(L, 25);
    assert(length(L) == 4);
    movePrev(L);
    assert(get(L) == 25);

    insertAfter(L, 35);
    moveNext(L);
    assert(get(L) == 35);
    printf("Test 5 passed: insertBefore/insertAfter\n");

    // Test 6: deleteFront(), deleteBack()
    deleteFront(L);
    assert(front(L) == 20);
    deleteBack(L);
    assert(back(L) == 30);
    printf("Test 6 passed: deleteFront/deleteBack\n");

    // Test 7: delete() at cursor
    moveFront(L);
    moveNext(L);
    delete(L);
    assert(length(L) == 2);
    printf("Test 7 passed: delete(cursor)\n");

    // Test 8: equals()
    List A = newList();
    List B = newList();
    append(A, 1);
    append(A, 2);
    append(B, 1);
    append(B, 2);
    assert(equals(A, B) == true);
    append(B, 3);
    assert(equals(A, B) == false);
    printf("Test 8 passed: equals\n");

;

    // Test 9: copyList()
    List C = copyList(A);
    assert(equals(A, C));
    assert(A != C);
    printf("Test 9 passed: copyList\n");

    // Test 10: join()
    List J = join(A, B);
    assert(length(J) == length(A) + length(B));
    printf("Test 10 passed: join\n");

    // Test 11: split()
    moveFront(J);
    moveNext(J);
    List S = split(J);
    assert(length(S) == 1);
    assert(length(J) == 4);
    printf("Test 11 passed: split\n");

    // Test 12: clear()
    clear(J);
    assert(length(J) == 0);
    assert(position(J) == -1);
    printf("Test 12 passed: clear\n");

    // Cleanup
    freeList(&L);
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&J);
    freeList(&S);

    printf("\nAll List ADT tests PASSED ✅\n");
    return 0;
}
