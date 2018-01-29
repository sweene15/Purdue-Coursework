#include "header1.h"
#include <stdio.h>
#include <stdlib.h>
main() {
 double x[];
 double y[];
 double z[];
 int vecSize, i, read;
 double result;
 int *vecSizePointer;
 vecSizePointer = &vecSize;
 int read_vecs(int *, double *, double *, double *);
 double calc_dist(int, double *, double *);
 void calc_sum(int, double *, double *, double *);
 void calc_diff(int, double *, double *, double *);
  
 read = read_vecs(vecSizePointer, x, y, z);
 FILE *f;
 f = fopen("vector_out.dat", "w");
 if(read != -1) {
  calc_sum(vecSize, x, y, z); 
  fprintf(f, "Component Sums: \n");
  for(i = 0; i < vecSize; i++) 
   fprintf(f, "Component #%d %f\n", (i+1), z[i]);
  calc_diff(vecSize, x, y, z);
   fprintf(f, "Component Differences: \n");
  for(i = 0; i < vecSize; i++)
   fprintf(f, "Component #%d %f\n", (i+1), z[i]);
  result = calc_dist(vecSize, x, y);
  fprintf(f, "Euclid Distance Result: %f\n", result);
 } else {
  fprintf(f, "Invalid Input");
 }
 fclose(f);
}
