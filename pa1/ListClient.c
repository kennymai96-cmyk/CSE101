#include <stdio.h>
#include <assert.h>
#include "List.h"

int main(void){

    // --- Test 1: newList() initializes correctly ---
    //List L = newList();
    //assert(L != NULL);

    // --- Test 2: freeList() sets L to NULL ---
    //freeList(&L);
    //assert(L == NULL);
    
    // test list
    List L = makeTestList(1, 2);
    //List M = makeTestList(3, 4);
    //List N = makeTestList(5, 6);

    //List O = join(L, M);
    split(L);
    printf("Length of your list after split is = %d\n", length(L));
    moveBack(L);
    //split(L);
    //printf("Length of your list after split is = %d\n", length(L));
    //printf("Length of your list is = %d\n", length(O));
    //printf("Front element is = %d\n", front(O));  
    //printf("Back element is = %d\n", back(O)); 
    
    printList(stdout, L);


    /*
    fprintf(stderr, "L=%p\n", (void*)L);
    //fprintf(stderr, "length(L) about to run...\n");
    printf("Length of your list is = %d\n", length(L));
    //fprintf(stderr, "front(L) about to run...\n");
    printf("Front node's data = %d\n", front(L));
    printf("Back node's data = %d\n", back(L));
    printf("Cursor position is = %d\n", position(L));
    printf("Element at cursor position is = %d\n", get(L));
    printf("Are list elements equal? = %d\n", equals(L, M));
    printf("Are list elements equal? = %d\n", equals(L, N));
    //deleteFront(L);
    printf("Length of your list is = %d\n", length(L));
    //deleteBack(L);
    printf("Length of your list is = %d\n", length(L));
    //delete(L);
    //printf("Length of your list is = %d\n", length(L));


    //moveBack(L);
    //printf("Position of your cursor after moveBack is = %d\n", position(L));
    //moveFront(L);
    //movePrev(L);
    printf("Position of your cursor is = %d\n", position(L));
    printf("Length of your list is = %d\n", length(L));
    //clear(L);
    //printf("Length of your list is = %d\n", length(L));
    //movePrev(L);
    //printf("Position of your cursor is = %d\n", position(L));
    //movePrev(L);
    //printf("Position of your cursor is = %d\n", position(L));
    //printf("Cursor element is = %d\n", get(L));
    //moveFront(L);
    //printf("Position of your cursor after moveFront is = %d\n", position(L)); 
    //moveNext(L);
    //printf("Position of your cursor after moveNext is = %d\n", position(L));
    //movePrev(L);
    //printf("Position of your cursor after movePrev is = %d\n", position(L));
    printf("Cursor element is = %d\n", get(L));
    set(L, 1);
    printf("Cursor element is = %d\n", get(L));
    prepend(L, 2);
    printf("Length of your list is = %d\n", length(L));
    printf("Front element is = %d\n", front(L));
    prepend(L, 3);
    printf("Front element is = %d\n", front(L));
    printf("Front element is = %d\n", back(L));
    append(L, 4);
    printf("Back element is = %d\n", back(L));

    printf("Length of your list is = %d\n", length(L));
    printf("Position of your cursor is = %d\n", position(L));
    insertAfter(L, 5);
    moveNext(L);
    printf("Cursor element is = %d\n", get(L));
    printf("Length of your list is = %d\n", length(L));
    insertBefore(L, 6);
    movePrev(L);
    printf("Cursor element is = %d\n", get(L));
    printf("Length of your list is = %d\n", length(L));

    copyList(L);
    printf("Length of your list is = %d\n", length(L));
    printf("Front element is = %d\n", front(L)); */    

    return 0;
}
