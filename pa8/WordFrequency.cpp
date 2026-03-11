//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA8
// WordFrequency.cpp
// Top-level file for Dictionary ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include "Dictionary.h"

using namespace std;

#define MAX_LINE 1024  // define max line length

int main(int argc, char *argv[]) {  // check for valid amount of inputs: input file, output file
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        exit(EXIT_FAILURE);
    }
    ifstream in(argv[1]);   // open input file for reading
    ofstream out(argv[2]);  // open output file for writing
    if (!in.is_open() || !out.is_open()) {  // check for valid input and output file
        cerr << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
    }
    // create new dictionary
    Dictionary D;
    // declare string to hold inputted line
    string line;
    while (getline(in, line)) {  // read text from input file
        int w = 0;               // define index to store valid char in word
        char word[256];          // set size of each word, assumes size < 255 including termination
        for (int i = 0; i < line.length(); i++) { // iterate thru each char in line
            if (isalpha((unsigned char)line[i])) {  // check for alpha char
                word[w++] = tolower(line[i]);       // store char into word
            }
            else if (w > 0) {  // terminate word if non-alpha encountered
                word[w] = '\0';  // terminate
                w = 0;           // reset word index
                string key = word;
                if (D.contains(key)) {  // if pair found, increment count
                    D.getValue(key)++;
                }
                else {                  // if not found set count to 1
                    D.setValue(key, 1);
                }
            }
        }
        // handle case of last word in line
        if (w > 0) {
            word[w] = '\0';
            string key = word;
            if (D.contains(key)) {
                D.getValue(key)++;
            }
            else {
                D.setValue(key, 1);
            }
        }
    }
    out << D;     // print dictionary
    in.close();   // close input file
    out.close();  // close output file
    return 0;
}