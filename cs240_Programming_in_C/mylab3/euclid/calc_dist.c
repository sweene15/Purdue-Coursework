#include "header1.h"
#include <stdio.h>
#include <math.h>

double calc_dist(int a, double *b, double *c) {
 
 double result = 0;
 int i;
 double tempDouble;
 printf("%d\n", a);
 i = 0;
 while(i < a) {
  printf("Subtracting %f from %f, squaring and adding to totali\n", b[i], c[i]);
  tempDouble = tempDouble + pow((b[i] - c[i]), 2); 
  i++;
 }
 printf("tempDouble: %f\n", tempDouble);
 result = sqrt(tempDouble);
 printf("result: %f\n", result); 
 return result;

}
