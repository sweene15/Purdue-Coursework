/* 	version 5 of z = x - y
	same as version 4 but uses separate
	function mycalc() to perform multiplication */ 

#include <stdio.h>

float mycalc(float, float, float *);

main() 
{
float x, y, z;

// read input
  scanf("%f %f",&x,&y);

// compute subtraction
  mycalc(x,y,&z);

// print result
  printf("result of %f - %f = %.2f\n", x, y, z);

}


/*	function mycalc(a,b) takes two
	arguments of type float, multiplies them and
	returns the result to the calling
	function */

float mycalc(float a, float b, float *c)
{

// subtract argument b from argument a
// and store the result in local variable c
  *c = a - b;
}
