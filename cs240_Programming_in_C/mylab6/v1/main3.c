// example that makes use of command-line arguments

#include <stdio.h>

int main(int argc, char **argv, char **environ)
{
int i;

/*
  printf("argc = %d\n", argc);

  for (i=0; i<argc; i++) {
	printf("argv[%d] = %s\n", i, argv[i]);
  }
*/

  while (*environ != NULL) {
	printf("%s\n", *environ);
	environ++;
  }

  return 0;

}
