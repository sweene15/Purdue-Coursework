#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void calc_sum(int a, double *b, double *c, double *d) {
 int i = 0;
 while(i < a) {
  d[i] = (b[i] + c[i]);
  i++;
  }
}
