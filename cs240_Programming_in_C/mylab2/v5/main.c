// C++ is a superset of C with OO (objective oriented) extensions.
// However, there are subtle differences that must be taken into account
// when porting code.

#include <stdio.h>

main()
{
int x;
void changeval(int &);

  x = 8;
  changeval(x);
  printf("%d\n",x);

}


void changeval(int &a)
{
  a = 3;
}
