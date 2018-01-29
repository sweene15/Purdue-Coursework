/* 	version 7 of z = x - y
	same as version 5 but puts declaration of
	mycalc() in a separate 
	header file, myheader.h */ 
#include <float.h>
#include <stdio.h>
#include "myheader.h"
#include <math.h>
int main() 
{
float x, y, z;

// read input
  scanf("%f %f",&x,&y);

// compute subtraction
  z = mycalc(x,y);

// print result
  printf("sine of %f plus cosine of %f = %.2f\n", x, y, z);

}
