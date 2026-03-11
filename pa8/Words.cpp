//-----------------------------------------------------------------------------
// Kenny Mai
// kemai
// 2026 Winter CSE101 PA8
// Words.cpp
// Top-level file for Dictionary ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789\n\r\f\v";
   // declare Dictionary
   Dictionary D;
   // declare to hold insertion index
   int index = 0;
   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   // read each line of input file, then count and print tokens 
   while( getline(in, line) )  {
      len = line.length();
      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      // while we have a token
      while( token!="" ){ 
         // insert if not in Dictionary and increment insertion index
         if(!D.contains(token)){
            D.setValue(token, index);
            index++;
         }
         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }
   // 
   out << "(";
   // goto begin of Dictionary
   D.begin();
   // iterate while iterator is not at last pair
   while(D.hasCurrent()){
      out << D.currentVal();
      D.next();
      if(D.hasCurrent()){
         out << ", ";
      }
   }
   out << ")" << endl;
   for(D.begin(); D.hasCurrent(); D.next()){
      out << D.currentKey() << endl;
   }
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
