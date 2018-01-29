/* yes/no client response translation tester.
 c[10] stores the client's input from stdin (i.e., keyboard)
 performed by function readinput().
 If input is string "ne" then readinput() returns 0.
 If input is string "oxi" then readinput() returns 1.
 Else -1 is returned. */

#include <stdio.h>

int readinput(char *);

main()
{
int x;
char c[10];

  x = readinput(c);

  if (x == 0)
	printf("client says %s which means yes\n", c);
  else if (x == 1)
	printf("client says %s which means no\n", c);
  else if (x == -1)
	printf("can't translate client response %s\n", c);
  else
	printf("abort: something is not right\n", c);

}
