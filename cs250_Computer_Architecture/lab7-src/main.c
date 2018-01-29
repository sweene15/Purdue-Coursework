//this is the main code in C

#include "stdio.h"
#include "string.h"
#include "stdlib.h"


extern char* sub_string(char *in_string, int start_index, int out_index);

int main()
{
  int start_index, end_index;
  char *in_string = malloc(256);
  char *out_string = malloc(256);

  printf("Please enter string input:\n");
  fgets(in_string, 256, stdin);

  if((strlen(in_string) > 0) && (in_string[strlen(in_string) -1] == '\n'))
    in_string[strlen(in_string) -1] == '0';

  printf("Please enter start index:");
  scanf("%d", &start_index);
  printf("Please enter end index:");
  scanf("%d", &end_index);

  printf("%s\n", sub_string(in_string, start_index, end_index));
  return 0;
}
