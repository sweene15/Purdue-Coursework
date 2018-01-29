#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t myCreateProcess(char *c) {
 pid_t pid;
 int a;
 pid = fork();
 if( pid == 0) {
   execlp(c, c, NULL);
   if(execlp(c,c,NULL) == -1)
    exit(1);
   fprintf(stdout, "Hello, world?\n");
   fflush(stdout);
 } else if( pid == -1) {
  return -1;
 }

}
