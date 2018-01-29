#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "simpleCommand.hh"
#include <regex.h>
#include <sys/types.h>

SimpleCommand::SimpleCommand() {
	// Create available space for 5 arguments
	_numOfAvailableArguments = 5;
	_numOfArguments = 0;
	_arguments = (char **) malloc( _numOfAvailableArguments * sizeof( char * ) );
}

static int myCompare (const void * a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}
 
void sort( char *arr[], int n)
{
    qsort (arr, n, sizeof (const char *), myCompare);
}


void SimpleCommand::insertArgument( char * argument ) {
	if ( _numOfAvailableArguments == _numOfArguments  + 1 ) {
		// Double the available space
		_numOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numOfAvailableArguments * sizeof( char * ) );
	}
	
	
	//escaping
	for(int i = 0; i < (int)strlen(argument); i++){
	  if(argument[i] == '\\'){
	    if(argument[i+1] == '\\'){
	      memmove(&argument[i], &argument[i+1], strlen(argument) - i);
	      i++;	
	    } else {
	      memmove(&argument[i], &argument[i+1], strlen(argument) - i);
	    }
	  }
	}


	//environ expansion

	//tilde expansion

	if(argument[0] == '~'){
	  if(strlen(argument) == 1){
	    argument = strdup(getenv("HOME"));
	  } else {
	    char* s = (char *)malloc(strlen(argument) + 8);
	    char *temp = (char *)"/homes/";
	    strcpy(s, temp);
	    strcat(s, argument + 1);
	    argument = strdup(s);
	  }
	}
	int isWildCard = 0;
	// wildcard expansion
	for(int i = 0; i < (int)strlen(argument); i++){
	  if(argument[i] == '*'){
            isWildCard = 1;
	    char *d;
	    char *str;
	    int j;
	    int isHome = 1;
	    for(j = i; j > 0; j--){ 
	      if(argument[j] == '/'){
	        isHome = 0;
		break;
	      }
	    }
	    if(i == 0){
	      d = strdup("."); 
	      str = argument;
	    } else {
	      if(isHome == 0){
	      	d = strdup(argument);
	      	*(d + j + 1) = '\0';
	        str = strdup(argument);
	        str = str + j + 1;
	      } else {
                d = strdup(".");
	        str = strdup(argument);
	      }
            }
	    //printf("TEST %s\n", str);
	    for(int k = 0; k < (int)strlen(str); k++){
	      if(str[k] == '*'){
                if(k == 0){
		  char* temp2 = (char *)malloc((int)strlen(str + 2));
		  temp2[0] = '.';
		  strcat(temp2, str);
		  str = strdup(temp2);
	          //printf("test %s\n", str);
		  k++;
		} else {
		  //printf("DANGER DANGER");
		  char* temp2 = (char *)malloc((int)strlen(str + 2));
		  char* temp3 = (char *)malloc((int)strlen(str + 2));
	          strncpy(temp2, str, k);
		  temp2[k] = '\0';
		  temp3 = str + k;
		  strcat(temp2, ".");
		  strcat(temp2, temp3);
		  str = strdup(temp2);
		  k++;
	        }
              }
	    }
	    //printf("* is at %d\n", i);
	    //printf("/ is at %d\n", j);
	    //printf("Str %s\n", str);
	    //printf("Dir %s\n", d);

	    DIR *dir = opendir(d);
	    struct dirent *entry;
	   
	    char* dirEntries[256];
	    int count = 0;
	    while((entry = readdir(dir))!= NULL){
		//printf("test\n");
	        if(entry->d_name[0] != '.'){
		  dirEntries[count] = strdup(entry->d_name);
		  count++;
		}
            }
	    sort(dirEntries, count);
	    for(int x = 0; x < count; x++){
	      char* name;
	      //name = strdup(entry->d_name);
	      name = dirEntries[x];
	      const char * regularExp = str;
	      const char * stringToMatch = name;
	      //printf("Matching to: %s\n", name);

              char regExpComplete[1024];
	      sprintf(regExpComplete, "^%s$", regularExp);

	      regex_t re;
	      int result = regcomp( &re, regExpComplete, REG_EXTENDED|REG_NOSUB);
	      if( result != 0 ) {
		fprintf( stderr, "%s: Bad regular expression \"%s\n", stringToMatch, regExpComplete);
	        exit(-1);
	      }
	      regmatch_t match;
              //printf("COMP: %s and %s\n", regExpComplete, stringToMatch);
	      result = regexec( &re, stringToMatch, 1, &match, 0);
	      //printf("Result: %d\n", result);
	      if( result == 0) {
		if(isHome == 0){
		  char* temp4;
		  temp4 = strdup(d);
		  //printf("String temp %s\n", temp4);
		  strcat(temp4, name);
		  name = strdup(temp4);
		}
		insertArgument(name);	
	      }
	      regfree(&re);
	    }

	  } else if (argument [i] == '?'){

	  }
	}

      if(isWildCard == 0){
	_arguments[ _numOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numOfArguments + 1] = NULL;
	
	_numOfArguments++;
       }
}
