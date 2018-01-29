// Use our own function changeval() instead of scanf() to illustrate
// passing by reference. We know the full code changeval().

#include <stdio.h>
main()
{
float *s;
float x;
  x = 8;
  changeval(&x); 
  s = &x;
  printf("%f\n",*s);
}
