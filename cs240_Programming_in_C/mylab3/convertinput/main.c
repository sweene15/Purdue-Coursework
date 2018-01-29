#include <stdio.h>

main()
{
char input[100] = "";
char output[100] = "";
char latestChar;
int i, j, tempInt;
char tempChar;
//Create Initial String
 for( i = 0; i <= 100; i++) {
  latestChar = getchar();
  if(latestChar != '\n')
   input[i] = latestChar;
  else
   break;
 }
 //Transform and put into Output String
 for ( j = 0; j <= 100; j++) {
  tempChar = input[j];
  tempInt = tempChar;
  if(65 <= tempInt && tempInt <= 90) {
   tempInt = tempInt + 32;
   tempChar = tempInt;
   output[j] = tempChar;

  }
  else if(30 <= tempInt && tempInt <= 39) {
   tempInt = 0;
   tempChar = tempInt;
   output[j] = tempChar;
   printf("test");
  }
  else {
   output[j] = tempChar;
  }
 }
 //Print both Input and Output
 printf("Input: %s\nOutput: %s\n", input, output);
}

