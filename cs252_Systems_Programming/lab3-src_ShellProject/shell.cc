#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "command.hh"
#include <sys/types.h>
#include <sys/wait.h>
int yyparse(void);


extern "C" void disp(int sig) {
  printf("\n");
  Command::_currentCommand.prompt();
}

extern "C" void killzombie(int sig) {
   int pid = wait3(0, 0, NULL);
   while(waitpid(-1, NULL, WNOHANG) > 0);
   if(Command::_currentCommand._background == 1){
     printf("[%d] exited.\n", pid);
     Command::_currentCommand.prompt();
   }
}

int main() {
	
	struct sigaction sa;
	sa.sa_handler = disp;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if(sigaction(SIGINT, &sa, NULL)){
	  perror("sigaction");
	  exit(2);
	}

	struct sigaction sa2;
	sa2.sa_handler = killzombie;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_RESTART;

	if(sigaction(SIGCHLD, &sa2, NULL)){
	  perror("sigchild");
	  exit(2);
	}


        	

	Command::_currentCommand.prompt();
	yyparse();
}
