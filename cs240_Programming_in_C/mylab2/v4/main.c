// Using pointers (i.e., variables that contain addresses) directly in
// a program.

#include <stdio.h>

main()
{
int x;
int *y;

  x = 2;
  printf("%d\n",x);
  printf("%p\n",&x);

  y = &x;
  printf("%d\n",*y);
  printf("%p\n",y);

}
