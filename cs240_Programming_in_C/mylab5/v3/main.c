#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SECRET "NOTSOSECRET"

main() {
 int run = 1;
 int lock = 0;
 char input[1000] = "";
 char lockInput[1000] = "";
 char latestChar, *token, *secondToken;
 char prompt[100] = ">";
 int i, ret;
 char initialPrompt[2] = ">";
 char un[9] = "Unlock: ";
 char cprompt[10] = "cprompt";
 char dprompt[10] = "dprompt";
 char quit1[5] = "QUIT";
 char quit2[2] = "Q";
 char quit3[5] = "quit";
 char quit4[2] = "q";
 char newLine[2] = "\n";
 char locker[6] = "tlock";
 char cheatSheet[5] = "cs";
 FILE *f;
 //Start the infinte loop
 while (run  == 1) {
  //Clear input
  for(i = 0; i <= 1000; i++) 
   input[i] = '\0';
  //Print prompt
  printf("%s", prompt);
  //get user input
  for(i = 0; i <= 1000; i++) {
   latestChar = getchar();
   if(latestChar != '\n')
    input[i] = latestChar;
   //Check if first char is newline
   else if(i == 0 && latestChar == '\n') {
    input[0] = '\n';
    break;
   }
   else
    break;
  }
  //Cut first command off to be interpreted
  token = strtok(input, " ");
  secondToken = strtok(NULL, " /");
  //QUIT case
  if ((strcmp(token, quit1) == 0) || (strcmp(token, quit2) == 0) || (strcmp(token, quit3) == 0) || (strcmp(token, quit4) == 0))
   run = 0;
  //CPROMPT case
  else if (strcmp(token, cprompt) == 0) {
   strcpy(prompt, secondToken); 
  }
  //DPROMPT case
  else if (strcmp(token, dprompt) == 0) {
   strcpy(prompt, initialPrompt);
  }
  //RETURN case
  else if (strcmp(token, newLine) == 0)
   system("clear");
  //LOCK CASE
  else if (strcmp(token, locker) == 0) {
   lock = 1; //LOCK IT UP
   while(lock == 1) {  //LOOP until unlocked
    printf("%s\n", un);
    for(i = 0; i <= 1000; i++) { //GET USER INPUT
     latestChar = getchar();
     if(latestChar != '\n')
      lockInput[i] = latestChar;
     else
      break;
    }
    //Comp. answer to key
    ret = strcmp(lockInput, SECRET);
    //If correct, unlock
    if(ret == 0)
     lock = 0;
   }
  }
  //Custom case, cheat sheet. Clears and presents valuable info.
  else if (strcmp(token, cheatSheet) == 0) {
   system("clear");
   printf("CHEAT SHEET:\n");
   printf("Presumably, important info would be stored here.\n");
  }
  //Anything else gets passed through the parent shell
  else {
   printf("about to run: %s\n", input);
   execl(input, input, NULL);
   fprintf(stdout, "Hello, world?\n");
   fflush(stdout);
  }
 }
}



