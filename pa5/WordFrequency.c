//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA5
// WordFrequency.c
// Top-level file for Dictionary ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Dictionary.h"

#define MAX_LINE 1024  // define max line length
#define INIT_CAP 64    // define initial capacity of the dynamic string array

int main(int argc, char *argv[]) {  // check for valid amount of inputs: input file, output file and file name
    
    // fprintf(stderr, "START\n");

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in  = fopen(argv[1], "r");  // open input file for reading
    FILE *out = fopen(argv[2], "w");  // open output file for writing

    if (in == NULL || out == NULL) {  // check for valid input and output file
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    // create new dictionary
    Dictionary D = newDictionary();
    char line[MAX_LINE];  // set line capacity

    while (fgets(line, MAX_LINE, in) != NULL) {  // read text from input file

        int w = 0;  // define index to store valid char in word
        char word[256]; // set size of each word, assumes size < 255 including termination

        for (int i = 0; line[i] != '\0'; i++) { // iterate thru each char in line until termination is hit
            if (isalpha((unsigned char)line[i])) {  // check for alpha char
                word[w++] = tolower(line[i]);  // store current char into word and increment to next index to avoid overwrite
            }
            else if (w > 0) {  // if already in middle of parsing a word and non-alpha char, terminate word
                
                word[w] = '\0';  // terminate
                w = 0;          // reset word index

                if(contains(D, word) == true){ // if pair found, insert and ++ count
                    int count = getValue(D, word);
                    setValue(D, word, count + 1);
                }
                else{ // if not found set count to 1
                    setValue(D, word, 1);
                }
            }
        }
        if (w > 0) { // handle case of last word in text file with no non-alpha chars to terminate word
            word[w] = '\0';

            if (contains(D, word) == true) {
                int count = getValue(D, word);
                setValue(D, word, count + 1);
            } else {
                setValue(D, word, 1);
            }
        }
    }
    printDictionary(out, D); // print dictionary
    freeDictionary(&D); // free memory of dictionary
    fclose(in); // close the input file
    fclose(out); // close the output file

    return 0;
}