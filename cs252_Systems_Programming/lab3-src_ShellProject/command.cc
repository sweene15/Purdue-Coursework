/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#include "command.hh"


Command::Command()
{
	// Create available space for one simple command
	_numOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
        _append = 0;
}

void Command::insertSimpleCommand( SimpleCommand * simpleCommand ) {
	if ( _numOfAvailableSimpleCommands == _numOfSimpleCommands ) {
		_numOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numOfSimpleCommands ] = simpleCommand;
	_numOfSimpleCommands++;
}

void Command:: clear() {
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inFile ) {
		free( _inFile );
	}

	if ( _errFile && _errFile != _outFile) {
		free( _errFile );
	}

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
}

void Command::print() {
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	

	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inFile?_inFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void Command::execute() {
	// Don't do anything if there are no simple commands
	if ( _numOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	if(strcmp(_simpleCommands[0]->_arguments[0], "exit") == 0)
	{
	  printf("Goodbye!\n");
	  exit(1);
        }
/*
	if(strcmp(_simpleCommands[0]->_arguments[0], "printenv") == 0)
	{
	  char **p = environ;
	  while(*p != NULL)
	  {
	    printf("%s\n", *p);
	    p++;
	  }
	  clear();
	  prompt();
	  return;
	}
*/
	if(strcmp(_simpleCommands[0]->_arguments[0], "setenv") == 0)
	{
	  if(setenv(_simpleCommands[0]->_arguments[1], _simpleCommands[0]->_arguments[2], 1) != 0)
	    perror("setenv");
	  clear();
	  prompt();
	  return;
	}
 	if(strcmp(_simpleCommands[0]->_arguments[0], "unsetenv") == 0)
	{
	  if(unsetenv(_simpleCommands[0]->_arguments[1]) != 0)
	    perror("unsetenv");
	  clear();
	  prompt();
	  return;
	}

	if(strcmp(_simpleCommands[0]->_arguments[0], "cd") == 0)
	{
	  if(_simpleCommands[0]->_numOfArguments > 1){
	    if(chdir(_simpleCommands[0]->_arguments[1]) != 0)
	      perror("chdir");
	  } 
          else {
	    char **p = environ;
	    p = p + 2;
	    //printf("%s\n", *p);
	    chdir(*p+5);
	  }
	  clear();
	  prompt();
	  return;
	}
	if(strcmp(_simpleCommands[0]->_arguments[0], "jobs") == 0)
	{
	  clear();
	  prompt();
	  return;
	}
	if(strcmp(_simpleCommands[0]->_arguments[0], "fg") == 0)
	{
	  clear();
	  prompt();
	  return;
	}
	if(strcmp(_simpleCommands[0]->_arguments[0], "bg") == 0)
	{
	  clear();
	  prompt();
	  return;
	}



        if(_err){
	  _err = 0;
	  clear();
          prompt();
          return;
        }
	
	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec
	int defaultIn = dup(0);
	int defaultOut = dup(1);
	int defaultErr = dup(2);
//	int fdin = 0;
//	int fdout = 0;
//	int fderr = 0;
	int fdpipe[2];
	pipe(fdpipe);
	int pid;

	for(int i = 0; i < _numOfSimpleCommands; i++){

	  //INPUT
	  if(_inFile == 0){
	    if(i == 0){		
	      dup2(defaultIn, 0);
	      //fprintf(stderr, "defaultIn %d\n", defaultIn);
	    }else{
	      int fdin = dup(fdpipe[0]);
	      dup2(fdin, 0);
	      close(fdin);
  	      //dup2(fdpipe[0], 0);
	      //fprintf(stderr, "tempPipeIn %d\n", fdpipe[0]);  
            }
	  }
	  else {
	    int fdin = open(_inFile, O_RDONLY);
	    dup2(fdin, 0);
	    close(fdin);
            //fprintf(stderr,"Read %d\n", fdin);
          }

          //OUTPUT
	  if(i != (_numOfSimpleCommands - 1)){  
	    //pipe(fdpipe);
	    int fdout = dup(fdpipe[1]);
	    dup2(fdout, 1);
	    close(fdout);
            //dup2(fdpipe[1], 1);
	    //fprintf(stderr, "tempPipeOut %d\n", fdpipe[1]);
          }
	  else{
	    if(_outFile == 0){
	      dup2(defaultOut, 1);
	      //fprintf(stderr,"defaultOut %d\n", defaultOut);
	    }
            else{
	      if(_append){
		int fdout = open(_outFile, O_WRONLY|O_APPEND|O_CREAT, 0666);
		dup2(fdout, 1);
		close(fdout);
		//fprintf(stderr, "OutAppend %d\n", fdout);
	      } else {
		int fdout = open(_outFile, O_WRONLY|O_TRUNC|O_CREAT, 0666);
		dup2(fdout, 1);
 		close(fdout);
		//fprintf(stderr, "Write %d\n", fdout);
	      }
            }
          } 
          //ERROR
	  if(_errFile == 0){
	    dup2(defaultErr, 2);
            //fprintf(stdout, "defaultErr %d\n", defaultErr);
          }
	  else{
	    if(_append){
              int fderr = open(_errFile, O_WRONLY|O_APPEND|O_CREAT, 0666);
	      dup2(fderr, 2);
	      close(fderr);
              //fprintf(stdout, "ErrAppend %d\n", fderr);
	    }
	    else {
	      int fderr = open(_errFile, O_WRONLY|O_TRUNC|O_CREAT, 0666);
	      dup2(fderr, 2);
	      close(fderr);
              //fprintf(stdout, "Err Write %d\n", fderr);
	    } 
	  }

        pid = fork();

	//fprintf(stderr,"PID: %d\n", getpid());
        if(pid == 0){
	  
	  close(defaultIn);
	  close(defaultOut);
	  close(defaultErr);
	  //close(fdpipe[0]);
	  close(fdpipe[1]);

	  if(strcmp(_simpleCommands[i]->_arguments[0], "printenv") == 0)
	  {
	    char **p = environ;
	    while(*p != NULL)
	    {
	      printf("%s\n", *p);
	      p++;
	    }
	    exit(1);
	  }
	  //fprintf(stderr, "BEING RUN %d\n", getpid());
          execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
	  _exit(1);
        } 
      }

      //fprintf(stderr, "WAITING FOR %d\n", pid);    
      //fprintf(stderr, "My Process ID: %d\n", getpid());
      //fprintf(stderr, "My Parent's ID: %d\n", getppid());
      

      dup2(defaultIn, 0);
      dup2(defaultOut, 1);
      dup2(defaultErr, 2);
      
      //waitpid(pid, 0, 0);
	
      close(defaultIn);
      close(defaultOut);
      close(defaultErr);	
      close(fdpipe[0]);
      close(fdpipe[1]);
 
      if( _background == 0){
        waitpid(pid, 0 ,0);
	clear();
	prompt();
      }
      
}

// Shell implementation

void Command::prompt() {\
  if(isatty(0)){
    printf("myshell>");
    fflush(stdout);
  }
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;
