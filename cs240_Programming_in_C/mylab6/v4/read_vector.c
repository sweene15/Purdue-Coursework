#include <stdio.h>
#include <stdlib.h>

int read_vector(int m, double *x, double *y) {
 char tempLine[];
 int i, j;
 FILE *f;
 
 tempLine = (char *) malloc(m*2 +1)
 x = (double *) malloc(m);
 y = (double *) malloc(m);

 f = fopen("vector.dat");
 fgets(tempLine, m *2 +1, f);
 j = 0;
 for(i = 0; i < m; i++) {
  if(tempLine[j] >= 48 && tempLine[j] <= 57){
   tempDouble = tempLine[j]
   x[i] = tempDouble;
  } else {
   return -1;
  }
  j+=2;
 }
}
