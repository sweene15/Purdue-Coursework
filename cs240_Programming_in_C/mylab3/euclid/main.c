#include <stdio.h>
#include <math.h>
#include "header1.h"

main() {
 double x[MAXSZ], y[MAXSZ];
 int vecsize;
 int *vecSizePointer;
 double (*xPointer)[MAXSZ];
 double (*yPointer)[MAXSZ];

 xPointer = &x;
 yPointer = &y;
 vecSizePointer = &vecsize;

  read_vecs(vecSizePointer, xPointer, yPointer);
  printf("VecSize: %d\n", vecsize);
  calc_dist(vecsize, xPointer, yPointer); 
 }
