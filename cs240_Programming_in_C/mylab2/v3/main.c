// Use our own function changeval() instead of scanf() to illustrate
// passing by reference. We know the full code changeval().

#include <stdio.h>
void changeval(int *);

main()
{
int x;

  x = 8;
  printf("%d\n",x);
  printf("%p\n",&x);
  changeval(&x);
  printf("%d\n",x);

}


void changeval(int *a)
{
  printf("%p\n",a);
  *a = 3;
}
