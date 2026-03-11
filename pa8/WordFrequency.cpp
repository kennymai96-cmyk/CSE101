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
    // delimiter characters 
    string delim = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;
    while (getline(in, line)) {  // read text from input file
        len = line.length();
        // find first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        string token = line.substr(begin, end - begin);
        // iterate through all tokens in this line
        while (token != "") {
            // convert token to lowercase
            for (size_t i = 0; i < token.length(); i++) {
                token[i] = tolower(token[i]);
            }
            // check if token already exists
            if (D.contains(token)) {
                D.getValue(token)++;   // increment frequency
            }
            else {
                D.setValue(token, 1);  // insert new word
            }
            // find next token
            begin = min(line.find_first_not_of(delim, end + 1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end - begin);
        }
    }
    out << D;     // print dictionary
    in.close();   // close input file
    out.close();  // close output file

    return 0;
}