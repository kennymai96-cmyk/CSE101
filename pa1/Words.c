//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA1
// Words.c
// Top-level file for List ADT
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "List.h"

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

    int capacity = INIT_CAP;  // set capacity at initial value
    int count = 0;           // set unique word count at 0
    char **words = malloc(capacity * sizeof(char *));  // allocate memory for dynamic string array

    char line[MAX_LINE];  // set line capacity

    while (fgets(line, MAX_LINE, in) != NULL) {  // read text from input file

        int w = 0;  // define index to store valid char in word
        char word[256]; // set size of each word, assumes size < 255 including termination

        for (int i = 0; line[i] != '\0'; i++) { // iterate thru each char in line until termination is hit
            if (isalpha((unsigned char)line[i])) {  // check for alpha char
                word[w++] = line[i];  // store current char into word and increment to next index to avoid overwrite
            }
            else if (w > 0) {  // if already in middle of parsing a word and non-alpha char, terminate word
                
                word[w] = '\0';  // terminate
                w = 0;          // reset word index
                bool duplicate = false; // init duplicate status as false
                
                for (int j = 0; j < count; j++) { // iterate thru each word in array
                    if (strcmp(words[j], word) == 0) { // check if current word equals one in array
                        duplicate = true; // if any match, set bool to true
                        break; // end loop
                    }
                }

                if (!duplicate) { // if no duplicate, proceed
                    if (count == capacity) { // check if total word count matches max
                        capacity *= 2; // double capacity
                        words = realloc(words, capacity * sizeof(char *)); // reallocate memory using new capacity
                    }

                    words[count] = malloc(strlen(word) + 1); // allocate memory for the string itself
                    strcpy(words[count], word); // copy word into current word count index
                    count++; // increment count for next word
                }
            }
        }

        if (w > 0) {  // handle case of last word in text file with no non-alpha chars to terminate word

            word[w] = '\0';  // terminate
            bool duplicate = false; // init duplicate status as false

            for (int j = 0; j < count; j++) { // iterate thru each word in array
                if (strcmp(words[j], word) == 0) { // check if current word equals one in array
                    duplicate = true; // if any match, set bool to true
                    break; // end loop
                }
            }

            if (!duplicate) { // if no duplicate, proceed
                if (count == capacity) { // check if total word count matches max
                    capacity *= 2; // double capacity
                    words = realloc(words, capacity * sizeof(char *)); // reallocate memory using new capacity
                }

                words[count] = malloc(strlen(word) + 1); // allocate memory for the string itself
                strcpy(words[count], word); // copy word into current word count index
                count++; // increment count for next word
            }
        }
    }

    List L = newList(); // make new empty list

    for (int i = 0; i < count; i++) { // iterate thru each word index

        if (length(L) == 0) { // if list is empty, append first index
            append(L, i);
        }
        else {
            moveFront(L); // start at front of list

            // check for valid position, compare current word with cursor word
            // if current word comes after cursor word, move to next word to compare
            while (position(L) >= 0 && strcmp(words[i], words[get(L)]) > 0) { 
                moveNext(L);
            }

            if (position(L) == -1) { // if current word is alphabetically after the whole list, append to end
                append(L, i);
            } 
            else { // if current word comes before cursor word alphabetically, insert before cursor word
                insertBefore(L, i);
            }
        }
    }

    // fprintf(stderr, "PRINTING\n");

    printList(out, L); // print indices of the sorted list
    fprintf(out, "\n");
    
    for(moveFront(L); position(L) >= 0; moveNext(L)){ // print the words of the sorted list separated by newline
        fprintf(out, "%s\n", words[get(L)]);
    }

    
    for(int i = 0; i < count; i++) {
        free(words[i]);
    }

    free(words); // free memory of dynamic string array
    freeList(&L); // free memory of the ordered list
    fclose(in); // close the input file
    fclose(out); // close the output file

    return 0;
}