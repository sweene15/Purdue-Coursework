#include <stdio.h>
#include <math.h>

void calc_diff(int a, double *b, double *c, double *d) {
 int i = 0;
 while(i < a) {
  d[i] = fabs(b[i] - c[i]);
  i++;
 }
}
