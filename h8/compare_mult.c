/* File:     compare_mult.c
 * Purpose:  Compare the performance of the hardware multiply, the
 *           basic algorithm outlined in the text in Figure 3.4, 
 *           and a proposed algorithm.  All three algorithms use unsigned 
 *           ints.
 *          
 * Compile:  gcc -g -Wall -o compare_mult compare_mult.c
 * Run:      ./compare_mult <number of multiplications>
 *
 * Input:    None
 * Output:   Elapsed time for the various multiplications.
 *
 * Note:     
 * 1.  DEBUG flag will print the results of the multiplies.
 * 2.  No check for overflow.
 * 3.  Use -O0 to prevent the compiler from optimizing away the
 *     function calls.
 * Runtimes: 	Runtimes for 1 multiplication
 * 		Time for hardware = 0.000000e+00 seconds
 * 		Time for basic = 9.536743e-07 seconds
 * 		Time for proposed = 4.053116e-06 seconds
 * 		
 * 		
 * 		Runtimes for 10 multiplications
 * 		Time for hardware = 0.000000e+00 seconds
 * 		Time for basic = 3.099442e-06 seconds
 * 		Time for proposed = 1.409054e-04 seconds
 * 		
 * 		
 * 		Runtimes for 100 multiplications
 * 		Time for hardware = 9.536743e-07 seconds
 * 		Time for basic = 2.908707e-05 seconds
 * 		Time for proposed = 2.177000e-03 seconds
 * 		
 * 		  		
 * 		Runtimes for 1000 multiplications
 * 		Time for hardware = 4.053116e-06 seconds
 * 		Time for basic = 1.239777e-04 seconds
 * 		Time for proposed = 1.278806e-02 seconds
 * 		
 * 		
 * 		Runtimes for 10000 multiplications
 * 		Time for hardware = 4.291534e-05 seconds
 * 		Time for basic = 1.255035e-03 seconds
 * 		Time for proposed = 1.053541e-01 seconds
 * 		
 * 		
 * 		Runtimes for 100000 multiplications
 * 		Time for hardware = 9.369850e-04 seconds
 * 		Time for basic = 1.783919e-02 seconds
 * 		Time for proposed = 1.009595e+00 seconds
 */
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

/* Largest value for one of the factors */
const int MAX = 10000;

/* Number of bits in an unsigned int */
#define BIT_COUNT sizeof(unsigned) << 3

unsigned Hardware(unsigned x, unsigned y);
unsigned Basic(unsigned x, unsigned y);
unsigned Proposed(unsigned x, unsigned y);

int main(int argc, char* argv[]) {
   unsigned iters, i, *x, *y, product;
   double start, finish, hardware_elapsed, basic_elapsed, proposed_elapsed;

   if (argc != 2) {
      fprintf(stderr, "usage: %s <number of multiplies>\n", 
            argv[0]);
      exit(0);
   }
   iters = strtol(argv[1], NULL, 10);
   x = malloc(iters*sizeof(int));
   y = malloc(iters*sizeof(int));

   /* Arrays of factors */
   srandom(1);
   for (i = 0; i < iters; i++) {
      x[i] = random() % MAX;
      y[i] = random() % MAX;
   }

   GET_TIME(start);
   for (i = 0; i < iters; i++) {
      product = Hardware(x[i],y[i]);
#     ifdef DEBUG
      printf("Hardware:  %u x %u = %u\n", x[i], y[i], product);
#     endif
   }
   GET_TIME(finish);
   hardware_elapsed = finish-start;

   GET_TIME(start);
   for (i = 0; i < iters; i++)  {
      product = Basic(x[i], y[i]);
#     ifdef DEBUG
      printf("Basic:  %u x %u = %u\n", x[i], y[i], product);
#     endif
   }
   GET_TIME(finish);
   basic_elapsed = finish-start;

   GET_TIME(start);
   for (i = 0; i < iters; i++)  {
      product = Proposed(x[i], y[i]);
#     ifdef DEBUG
      printf("Proposed:  %u x %u = %u\n", x[i], y[i], product);
#     endif
   }
   GET_TIME(finish);
   proposed_elapsed = finish-start;

   printf("Time for hardware = %e seconds\n", hardware_elapsed);
   printf("Time for basic = %e seconds\n", basic_elapsed);
   printf("Time for proposed = %e seconds\n", proposed_elapsed);

   free(x);
   free(y);

   return 0;
}

/*-------------------------------------------------------------------
 * Function:  Hardware
 * Purpose:   Multiply two numbers and return their product
 */
unsigned Hardware(unsigned x, unsigned y) {
   return x*y;
}  /* Mult */


/*-------------------------------------------------------------------
 * Function:  Basic
 * Purpose:   Multiply two numbers and return their product.  Use
 *            the basic algorithm outlined in the text
 */
unsigned Basic(unsigned x, unsigned y) {
   int product = 0;
   int i;
   for(i = 0; i < 32; i ++){
      if(x & 1){
         product += y;
      }
      y <<= 1;
      x >>= 1;
   }
   return product;
}  /* Mult */


/*-------------------------------------------------------------------
 * Function:  Proposed
 * Purpose:   Multiply two numbers using a proposed algorithm and
 *            return their product
 */
unsigned Proposed(unsigned x, unsigned y) {
   // multiplier and multiplicand >= 0
   int product = 0;
   int i;
   for (i = 0; i < y; i++){
      product += x;
   }
   return product;
}  /* Proposed */