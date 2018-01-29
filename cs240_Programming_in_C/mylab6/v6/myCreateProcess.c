#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

pid_t myCreateProcess(char *c) {
 pid_t pid;
 char *s[4];
 char *temp;
 char *tokenOne, *tokenTwo, *tokenThree;

 tokenOne = strtok(c ," ");
 tokenTwo = strtok(NULL, " ");
 tokenThree = strtok(NULL, " ");

 s[0] = tokenOne;
 s[1] = tokenTwo;
 s[2] = tokenThree;
 s[3] = '\0';

 
 pid = fork();
 if( pid == 0) {
   execvp(s[0], s);;
   if(execvp(s[0], s) == -1)
    exit(1);
   fprintf(stdout, "Hello, world?\n");
   fflush(stdout);
 } else if( pid == -1) {
  return -1;
 }

}
