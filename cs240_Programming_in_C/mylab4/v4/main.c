#include <stdlib.h>
#include <stdio.h>

main()
 {
 char input[100];
 int a, i;
 unsigned int e;
 unsigned int getbits(unsigned int, int);
 //Recive user input
 printf("Enter an integer: ");
 scanf("%s", input);
 //Convert to int
 a = atoi(input); 
 //Loops through all 32 bits, in pairs staring at the two LSBs
  for(i = 1; i <= 31; i+=2) {
  //Function used to get bits, seen below.
   e = getbits(a, i);
   //Switch checks for each of the possible values held between two bits, 0, 1, 2 and 3. 
   //Prints Dec, Hex, Oct, Binary values, in that order.
   switch(e) {
     case 0 :
      printf("Decimal: %u\nHexidecimal: 0x0\nOctal: 0o0\nBinary: 00\n\n", e);
      break;
     case 1 :
      printf("Decimal: %u\nHexidecimal: 0x1\nOctal: 0o1\nBinary: 01\n\n", e);
      break;
     case 2 :
      printf("Decimal: %u\nHexidecimal: 0x2\nOctal: 0o2\nBinary: 10\n\n", e);
      break;
     case 3 :
      printf("Decimal: %u\nHexidecimal: 0x3\nOctal: 0o3\nBinary: 11\n\n", e);
      break;
     default  :
      break;
    }
   } 
 }

 //Function that returns the two LSB. Slightly modified version of an example from K & R
 unsigned int getbits(unsigned int x, int p)
 {
  return (x >> (p-1)) & ~(~0 << 2);
 } 
