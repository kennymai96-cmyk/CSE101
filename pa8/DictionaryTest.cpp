//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA8
// DictionaryTest.cpp
// Test file for Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main(){
    // create dictionary and insert key-value pairs
    Dictionary A;
    A.setValue("d",4);
    A.setValue("b",2);
    A.setValue("a",1);
    A.setValue("c",3);
    A.setValue("f",6);
    A.setValue("e",5);
    A.setValue("g",7);
    // print inorder traversal
    cout << "Inorder traversal:\n";
    cout << A.to_string() << endl;
    // print preorder traversal to verify RB colors
    cout << "Preorder (with colors):\n";
    cout << A.pre_string() << endl;
    // test iterator functions
    cout << "Forward iteration:\n";
    A.begin();
    while(A.hasCurrent()){
        cout << A.currentKey() << " : " << A.currentVal() << endl;
        A.next();
    }
    cout << "Reverse iteration:\n";
    A.end();
    while(A.hasCurrent()){
        cout << A.currentKey() << " : " << A.currentVal() << endl;
        A.prev();
    }
    // test remove() using RB_Delete
    cout << "\nRemoving key 'd'\n";
    A.remove("d");
    cout << A.to_string() << endl;
    // test copy constructor
    cout << "Testing copy constructor\n";
    Dictionary B(A);
    cout << B.to_string() << endl;
    // test equals()
    cout << "A equals B? ";
    cout << (A.equals(B) ? "true\n" : "false\n");
    // modify copy to confirm deep copy
    B.setValue("z",26);
    cout << "\nAfter modifying B:\n";
    cout << "A:\n" << A << endl;
    cout << "B:\n" << B << endl;
    // test assignment operator
    cout << "Testing assignment operator\n";
    Dictionary C;
    C = A;
    cout << C.to_string() << endl;
    // test clear()
    cout << "Clearing C\n";
    C.clear();
    cout << "Size of C: " << C.size() << endl;

    return 0;
}