/* 	version 6 of z = x - y
	same as version 5 but puts mycalc()
	in a separate file, mycalc.c */ 

#include <stdio.h>

float mycalc(float, float);

main() 
{
float x, y, z;

// read input
  scanf("%f %f",&x,&y);

// compute subtraction
  z = mycalc(x,y);

// print result
  printf("result of %f minus %f is %.2f\n", x, y, z);

}
