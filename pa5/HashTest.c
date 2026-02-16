//-----------------------------------------------------------------------------
// HashTest.c
// Demonstrates computation of hash codes, and probe sequences.
//
//      compile:  gcc -o HashTest HashTest.c
//
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


typedef char* keyType;
typedef uint64_t codeType;


// print_binary_64()
// Prints a hash code as a bit string
void print_binary_64(codeType n) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", (int)((n >> i) & 1));
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}



// hash()
// Returns the hash code for key k.
codeType hash(keyType k) {
   codeType magicNumber1 = 0xcbf29ce484222325;
   codeType magicNumber2 = 0x100000001b3;
   codeType result = magicNumber1;
   codeType nextChar = *k;          // get 1st char in k
   while( nextChar ) {              // while not at end of k
      result ^= nextChar;           //    result = result (exor) nextChar
      result *= magicNumber2;       //    result = result * magicNumber2
      nextChar = *(++k);            //    get next char 
   }
   return result;
}


// probe()
// Returns the ith term in the probe sequence for code. This function is denoted h(k,i),
// and given in the Dictionary handout, second example in the hash table section.
size_t probe(codeType code, size_t arr_size, size_t i){
   codeType h1 = code & (arr_size-1);              // code % arr_size
   codeType h2 = 2*(code & (arr_size/2 - 1)) + 1;  // 2*(code % arr_size/2) + 1
   return (h1 + i*h2) & (arr_size-1);              // (h1 + i*h2) % arr_size
}

int main(void){
   
   keyType A[] = {"one","two","three","four","five","six","seven","eight",
                   "nine","ten","eleven","twelve","thirteen","fourteen",
                   "fifteen","sixteen","seventeen","eighteen","nineteen",
                   "twenty","twenty-one","twenty-two","twenty-three","twenty-four",
                   "twenty-five","twenty-six","twenty-seven","twenty-eight",
                   "twenty-nine"};
   int i, j, slot, n=29;
   int tableSize = 8;
   codeType code;

   printf("\n");
   printf("key   : code                 : probe sequence\n");
   printf("-----------------------------------------------------\n");
   for( i=0; i<n; i++ ){
      code = hash(A[i]);
      printf("%-5s : %-20lu : ", A[i], code);
      for( j=0; j<tableSize; j++ ){
         slot = probe(code, tableSize, j);
         printf("%d%s", slot, (j<tableSize-1) ? ", " : "");
      }
      printf("\n");
   }
   printf("\n");

   return EXIT_SUCCESS;
}

/* Program Output:

key   : code                 : probe sequence
-----------------------------------------------------
one   : 1875936269717626031  : 7, 6, 5, 4, 3, 2, 1, 0
two   : 6274872286310602505  : 1, 4, 7, 2, 5, 0, 3, 6
three : 6517818557876028835  : 3, 2, 1, 0, 7, 6, 5, 4
four  : 15939363302044458469 : 5, 0, 3, 6, 1, 4, 7, 2
five  : 12287250767515649397 : 5, 0, 3, 6, 1, 4, 7, 2
six   : 9387906364303253323  : 3, 2, 1, 0, 7, 6, 5, 4
seven : 87145300798591006    : 6, 3, 0, 5, 2, 7, 4, 1
eight : 18017151228111474160 : 0, 1, 2, 3, 4, 5, 6, 7
nine  : 647416338075027509   : 5, 0, 3, 6, 1, 4, 7, 2
ten   : 6261360387914166676  : 4, 5, 6, 7, 0, 1, 2, 3
eleven : 455078951784957408   : 0, 1, 2, 3, 4, 5, 6, 7
twelve : 4646686563101842196  : 4, 5, 6, 7, 0, 1, 2, 3
thirteen : 13749986473896072502 : 6, 3, 0, 5, 2, 7, 4, 1
fourteen : 13759621834300268481 : 1, 4, 7, 2, 5, 0, 3, 6
fifteen : 4212824814348254602  : 2, 7, 4, 1, 6, 3, 0, 5
sixteen : 18328325646107179243 : 3, 2, 1, 0, 7, 6, 5, 4
seventeen : 978367884149099750   : 6, 3, 0, 5, 2, 7, 4, 1
eighteen : 629081567556615280   : 0, 1, 2, 3, 4, 5, 6, 7
nineteen : 13138027973546970161 : 1, 4, 7, 2, 5, 0, 3, 6
twenty : 3365854472618251336  : 0, 1, 2, 3, 4, 5, 6, 7
twenty-one : 5181563454310590093  : 5, 0, 3, 6, 1, 4, 7, 2
twenty-two : 2036970094059643367  : 7, 6, 5, 4, 3, 2, 1, 0
twenty-three : 3819873815899507997  : 5, 0, 3, 6, 1, 4, 7, 2
twenty-four : 14154832914537533819 : 3, 2, 1, 0, 7, 6, 5, 4
twenty-five : 12842472328121236959 : 7, 6, 5, 4, 3, 2, 1, 0
twenty-six : 2802617215194998589  : 5, 0, 3, 6, 1, 4, 7, 2
twenty-seven : 9291936453228502176  : 0, 1, 2, 3, 4, 5, 6, 7
twenty-eight : 1492846518626941626  : 2, 7, 4, 1, 6, 3, 0, 5
twenty-nine : 4463243461303543695  : 7, 6, 5, 4, 3, 2, 1, 0

*/
