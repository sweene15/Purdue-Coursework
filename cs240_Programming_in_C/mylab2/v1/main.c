// Program to illustrate passing by address (or reference)
// vs. passing by value.

#include <stdio.h>

main()
{
int *u;
int s;

  *u = 8;
  scanf("%d",u);
  printf("%d\n",*u);
  // format %p is for printing address (i.e., pointer)
  printf("%p\n",&u);

}
