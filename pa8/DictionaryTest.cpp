//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA8
// DictionaryuTest.cpp
// Unit Test file for Dictionary ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "Dictionary.h"

int main() {
    Dictionary A;

    A.setValue("d",4);
    A.setValue("b",2);
    A.setValue("a",1);
    A.setValue("c",3);
    A.setValue("f",6);
    A.setValue("e",5);

    cout << A.size() << endl;

    cout << A.contains("c") << endl;
    cout << A.getValue("c") << endl;

    cout << A.to_string() << endl;
    cout << A.pre_string() << endl;

    A.begin();
    if(A.hasCurrent()){
        cout << A.currentKey() << " " << A.currentVal() << endl;
    }

    A.next();
    if(A.hasCurrent()){
        cout << A.currentKey() << " " << A.currentVal() << endl;
    }

    A.end();
    if(A.hasCurrent()){
        cout << A.currentKey() << " " << A.currentVal() << endl;
    }

    A.prev();
    if(A.hasCurrent()){
        cout << A.currentKey() << " " << A.currentVal() << endl;
    }

    Dictionary B(A);

    cout << B.to_string() << endl;

    cout << A.equals(B) << endl;

    B.remove("c");
    cout << B.to_string() << endl;

    B.clear();
    cout << B.size() << endl;

    Dictionary C;

    C = A;

    cout << C.to_string() << endl;

    cout << (A == C) << endl;

    cout << A << endl;

    return 0;
}