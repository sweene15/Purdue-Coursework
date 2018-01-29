/*	function mycalc(a,b) takes two
	float arguments, subtracts them and
	returns the result to the calling
	function */
#include <float.h>
#include <math.h>
float mycalc(float a, float b)
{
float c;
// calculate sine and cosine values
  a = sin(a);
  b = cos(b);
// subtract
  c = a + b;

  return c;
}
