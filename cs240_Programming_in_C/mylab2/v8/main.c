// Pointers and arrays

#include <stdio.h>
#define MYDEBUG 1
main()
{
int *h;
int x;
  x = 100;
  h = &x;
  *(h+1) = 200;
  *(h+2) = 300;
  printf("%d\n",*h);
  printf("%d\n",*(h+1));
  printf("%d\n",*(h+2));

}
