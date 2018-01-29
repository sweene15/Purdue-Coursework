#include "stdio.h"
#include "string.h"
#include "stdlib.h"


char* sub_string(char *in_string, int start_index, int end_index){
/*
  printf("%s\n", in_string);
  printf("%d\n", start_index);
  printf("%d\n", end_index);
  return in_string;
*/
  int len = end_index - start_index + 1;
  char* out = malloc(len + 1);
  char* temp = malloc (strlen(in_string));
  strcpy(temp, in_string);
  int i;
  for(i = 0; i < len; i++){
    out[i] = temp[i + start_index - 1];
  }
  out[len] = '\0';
  return out;
}
