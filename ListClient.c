#include <stdio.h>
#include <assert.h>
#include "List.h"

int main(void){

    // --- Test 1: newList() initializes correctly ---
    List L = newList();
    assert(L != NULL);

    // --- Test 2: freeList() sets L to NULL ---
    freeList(&L);
    assert(L == NULL);

    // --- Test 3: length function
    // printf("Length (expect 0): %d\n", length(L));

    return 0;
}
