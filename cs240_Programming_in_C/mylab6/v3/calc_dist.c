#include <stdio.h>
#include <stdio.h>
#include <math.h>

double calc_dist(int a ,double *b, double *c) {
 double result = 0;
 int i = 0;
 double tempDouble;
 while(i < a) {
  tempDouble = tempDouble + pow((b[i] -c[i]), 2);
  i++;
 }
 result = sqrt(tempDouble);
 return result;

}
