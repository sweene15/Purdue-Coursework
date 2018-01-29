// Basic, rudimentary way to track down where in code a run-time error
// occurs. Use fflush() to ensure buffered output is flushed.

#include <stdio.h>

#define MYDEBUG 1

main()
{
int x;
void changeval(int *);

  x = 8;

#ifdef MYDEBUG
fprintf(stderr, "ok 1\n");
fflush(stdout);
#endif

  changeval(&x);

#ifdef MYDEBUG
printf("ok 2\n");
fflush(stdout);
#endif

  printf("%d\n",x);
  changeval(x);

#ifdef MYDEBUG
printf("ok 3\n");
fflush(stdout);
#endif

  printf("%d\n",x);

}


void changeval(int *a)
{
  *a = 3;
}
