/* File:     compute.c
 *
 * Purpose:  Linux program that subtracts two user-input long
 *			 ints then adds another to that result.  Calls x86 
 *           assembly function to do the calculation.
 *
 * Compile:  gcc -o compute compute.c compute.s -I.
 * Run:      ./compute
 *
 * Input:    Three long ints
 * Output:   The computation of the three ints
 *
 * Notes:     
 * 1. This version should be run on a 64-bit system.
 */

#include <stdio.h>

long Compute(long a, long b, long c);

int main(void) {
   long a, b, c, d;

   printf("Enter three ints\n");
   scanf("%ld%ld%ld", &a, &b, &c);

   d = Compute(a, b, c);

   printf("The result is %ld\n", d);

   return 0;
}