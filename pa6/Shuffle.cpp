//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA6
// Shuffle.cpp
// Top-Level file for List ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// shuffle function
// takes in a list pointer and performs a rifle shuffle
void shuffle(List& D){
    // declare lists for each half
    List front;
    List back;
    // move to front of input list
    D.moveFront();
    // iterate thru half of list and append to front list
    while(D.position() < (D.length() / 2)){
        front.insertAfter(D.moveNext());
        front.moveNext();
    }
    // iterate thru list and append to back list
    while(D.position() < D.length()){
        back.insertAfter(D.moveNext());
        back.moveNext();
    }
    // clear D to prepare for recombination
    D.clear();
    // move to front of each list
    D.moveFront();
    front.moveFront();
    back.moveFront();
    // iterate thru lists using back's length, and its element first
    while(back.position() < back.length()){
        D.insertAfter(back.moveNext());
        D.moveNext();
        // iterate thru front after appending back
        if(front.position() < front.length()){
            D.insertAfter(front.moveNext());
            D.moveNext();
        }
    }
}

// main function
// Computes shuffle order for deck sizes up to n
int main(int argc, char* argv[]){
    // check for correct argument size
    if(argc != 2){
        std::cerr << "Incorrect input!";
        return 1;
    }
    // print headers for output
    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;
    // take in input denoting deck size
    // convert from string to int
    int size = std::stoi(argv[1]);
    // iterate thru deck size of n to track order
    for(int n = 1; n <= size; n++){
        // create empty list and move to front of it
        List D;
        D.moveFront();
        // iterate thru deck and insert into list sequentially
        for(int i = 0; i < n; i++){
            D.insertAfter(i);
            D.moveNext();
        }
        // copy OG list
        List D_copy = D;
        // define var to keep order count
        int count = 0;
        // do an initial shuffle
        shuffle(D);
        count++;
        while(!(D == D_copy)){
            shuffle(D);
            count++;
        }
        // print to stdout 
        std::cout << n << " " << count << std::endl;
    }
    // return int for main
    return 0;
}