// Pointers, program memory, and silent run-time errors.
// Good programming practice.

#include <stdio.h>

main()
{
int i;
int a[5];

  for(i=0; i<5; i++)
	a[i] = i;

  for(i=0; i<5; i++)
  	printf("%d\n",*(a+i));

  for(i=0; i<7; i++)
	a[i] = i;

  for(i=0; i<7; i++)
	printf("%d\n",*(a+i));

}
