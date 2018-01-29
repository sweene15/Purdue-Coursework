#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

main() {
//Variables
char input[100] = "";
char latestChar, *firstInput, *secondInput, *thirdInput; 
unsigned char buffer[BUFFER_SIZE];
char tempChar[9] = "";
int i, j, k, pos, num, fileLength, tempInt;
FILE *f;
 //Read User Input, Create Intial String
 for (i = 0; i <= 100; i++) {
  latestChar = getchar();
  if(latestChar != '\n')
   input[i] = latestChar;
  else
   break;
 }
 //Tokenize Input String
 firstInput = strtok(input, " ");
 secondInput = strtok(NULL, " ");
 thirdInput = strtok(NULL, " ");
 //printf("%s\n%s\n%s", firstInput, secondInput, thirdInput);
 //Set position
 pos = atoi(firstInput);
 //Set number
 num = atoi(secondInput);
 //Open Stream
 f = fopen(thirdInput, "r");
 //Determine the length of the file
 fseek(f, 0, SEEK_END);
 fileLength = ftell(f);
 fseek(f, 0, SEEK_SET);
 //Determine if pos+num > length
 if(!((pos + num) > fileLength)) {
  //Set stream position
  fseek(f, pos, SEEK_SET);
  //Read, place in a array buffer
  fread(buffer, 1, num, f);
  //Convert ASCII to binary, store in array and print
  //Converted buffer stores strings that hold binary values
  char convertedBuffer[num-1][9];
  //Loop through all values in buffer
  for(i = 0; i < num; i++) {
   k = 7; //K is used to count down from 7 to 0 inside second for loop
   //Pulls bits from the buffer value, sets each to tempChar, which is a string that holds all 0s and 1s that make up the binary value
   for(j = 0; j < 8 ; j++) {
    tempChar[k] = (buffer[i] >> (j)) & ~(~0 << 1) ;
    tempChar[k] = tempChar[k] + 48;
    k--;
   }
   //set last value in tempChar to null, this prevents garbage
   tempChar[9] = 0;
   //Copy tempChar into the array of strings
   strcpy(convertedBuffer[i], tempChar);
   //Print Binary
   printf("%s",convertedBuffer[i]);
   // determine if first value is a 0
   if(tempChar[0] == 48 && buffer[i] >= 33 && buffer[i] <= 126)
   //if so, print off the char stored in buffer
    printf(" %c", buffer[i]);
   printf("\n");
  }
 } else {
  printf("The values you entered exceed the maximum number of bytes in the file");
 }
}
