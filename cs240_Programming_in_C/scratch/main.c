#include <stdio.h>
#include <string.h>
//TOKEN TEST
main()
{
 char * token;
 char inputDimension[100];
 const char s[2] = " ";
 char *a = "test";
 scanf("%s", inputDimension);
 printf("%s", a);
 token = strtok(inputDimension, s);
 printf("%s", a);
 printf("%s", token);



}
