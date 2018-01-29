#include <stdio.h>
#include <string.h>
#include "header1.h"
#include <stdlib.h>

int read_vecs(int *vecSize, double *x, double *y, double *z) {
 char lineOne[100];
 char lineTwo[100];
 char lineThree[100];
 int vecValue, i, j, tempInt;
 double tempDouble = 0;
//OPEN AND READ FROM FILE
 FILE *f;
 f = fopen("vector_in.dat", "r");
 fgets(lineOne, 100, f);
 fgets(lineTwo, 100, f);
 fgets(lineThree, 100, f);
 fclose(f);
//WORK WITH THE FIRST LINE, SET VECSIZE
 if(lineOne[4] >= 48 && lineOne[4] <= 57) {
  vecValue = lineOne[4] - 48;
  *vecSize = vecValue;

//MALLOC, and SET values to 0
  x = (double *) malloc(vecValue);
  memset(x, 0, vecValue);
  y = (double *) malloc(vecValue);
  memset(y, 0, vecValue);
  z = (double *) malloc(vecValue);
  memset(z, 0, vecValue);

//SET VALUES
  j = 8;
  for(i = 0; i < vecValue; i ++) {
   if(lineTwo[j] >= 48 && lineTwo[j] <= 57) {
    tempDouble = lineTwo[j] - 48;
    *(x + i)  = tempDouble;
    j+=2;
   } else {
    return -1;
   }
  }
  j = 8;
  for(i = 0; i < vecValue; i ++) {
   if(lineThree[j] >= 48 && lineThree[j] <= 57) {
    tempDouble = lineThree[j] - 48;
    *(y + i)  = tempDouble;
    j+=2;
   } else {
    return -1;
   }
  }
 } else {
  return -1;
 }
}




