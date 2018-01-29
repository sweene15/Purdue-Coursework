#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_mat(int *n, int *m, double **a) {
 char lineOne[100];
 char tempLine[100];
 int nValue, mValue, *j, k, l, p;
 size_t i;
 FILE *f;

 //OPEN File, read m and n values, and set
 f = fopen("matrix.dat", "r");
 fgets(lineOne, 100, f);
 if(lineOne[0] >= 48 && lineOne[0] <= 57 && lineOne[2] >= 48 && lineOne[2] <=57) {
  nValue = lineOne[0] - 48;
  mValue = lineOne[2] - 48;
  *n = nValue;
  *m = mValue;
 }
 //Allocate Memory for 2D Array
 a = malloc(nValue * sizeof *a + (nValue * (nValue * (mvalue * sizeof ** a))));
 j = a + nValue;
 for(i = 0; i < nValue; i++) {
 a[i] = j + i * mValue;
 }
 //Read and Set Array Values
 //DOUBLE LOOP
 for(k = 0; k < nValue; k++) {
  p = 0;
  for(l = 0; l < mValue; l++) {
   //Get values, set to a temporary line
   fgets(tempLine, 100, f);
   fclose();
   //determine if int, if so, convert and store in a
   if(tempLine[p] >= 48 && tempLine[p] <= 57) {
    tempDouble = tempLine[p] - 48;
    *(a + ((k*m)+l) = tempDouble;
    p+=2;
   } else {
    return -1;
   }
  }
 }
}
