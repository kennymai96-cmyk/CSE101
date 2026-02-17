//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA5
// DictionaryTest.c
// Unit Tests for Dictionary ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Dictionary.h"

int main(void){
    Dictionary D = newDictionary();

    setValue(D, "one", 1);
    setValue(D, "two", 2);
    setValue(D, "three", 3);
    setValue(D, "four", 4);
    setValue(D, "five", 5);

    printDiagnostic(stdout, D);

    printf("size: %d\n", size(D));
    printf("contains two: %d\n", contains(D, "two"));
    printf("value three: %d\n", getValue(D, "three"));

    removeKey(D, "two");
    removeKey(D, "four");

    printDiagnostic(stdout, D);

    setValue(D, "six", 6);
    setValue(D, "seven", 7);
    setValue(D, "eight", 8);

    printDiagnostic(stdout, D);

    Dictionary C = copy(D);
    printf("equals copy: %d\n", equals(D, C));

    printDictionary(stdout, D);

    clear(D);
    printDiagnostic(stdout, D);

    freeDictionary(&C);
    freeDictionary(&D);

    return 0;
}
