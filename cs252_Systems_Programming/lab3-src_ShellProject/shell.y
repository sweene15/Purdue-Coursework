
/*
 * CS-252
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%code requires 
{
#include <string>

#if __cplusplus > 199711L
#define register      // Deprecated in C++11 so remove the keyword
#endif
}

%union
{
  char        *string_val;
  // Example of using a c++ type in yacc
  std::string *cpp_string;
}

%token <string_val> WORD
%token NOTOKEN GREAT NEWLINE LESS TWOGREAT GREATAMP DOUBLEGREAT DOUBLEGREATAMP PIPE AMP

%{
//#define yylex yylex
#include <cstdio>
#include "command.hh"

void yyerror(const char * s);
int yylex();

%}

%%

goal:
  commands
  ;

commands:
  command
  | commands command
  ;

command: simple_command
       ;

simple_command:	
  pipe_line iomodifier_list back_flag NEWLINE {
    /*printf("   Yacc: Execute command\n");*/
    Command::_currentCommand.execute();
  }
  | NEWLINE 
  | error NEWLINE { yyerrok; }
  ;

command_and_args:
  command_word argument_list {
    Command::_currentCommand.
    insertSimpleCommand( Command::_currentSimpleCommand );
  }
  ;

argument_list:
  argument_list argument
  | /* can be empty */
  ;

argument:
  WORD {
    /*printf("   Yacc: insert argument \"%s\"\n", $1);*/
    Command::_currentSimpleCommand->insertArgument( $1 );\
  }
  ;

command_word:
  WORD {
    /*printf("   Yacc: insert command \"%s\"\n", $1);*/
    Command::_currentSimpleCommand = new SimpleCommand();
    Command::_currentSimpleCommand->insertArgument( $1 );
  }
  ;

iomodifier_opt:
  GREAT WORD {
    /*printf("   Yacc: insert output \"%s\"\n", $2);*/
    if(Command::_currentCommand._outFile)
      yyerror("Ambiguous output redirect.\n");
    Command::_currentCommand._outFile = $2;
  }
  | LESS WORD {
    /*printf("   Yacc: insert input \"%s\"\n", $2);*/
    Command::_currentCommand._inFile = $2;
  }
  | TWOGREAT WORD{
    /*printf("   Yacc: insert err \"%s\"\n", $2);*/
    Command::_currentCommand._errFile = $2;	
  }
  | GREATAMP WORD{ 
    /*printf("   Yacc: insert output and err \"%s\"\n", $2);*/
    if(Command::_currentCommand._outFile)
      yyerror("Ambiguous output redirect.\n");
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
  }
  | DOUBLEGREAT WORD { 
    /*printf("   Yacc: append output \"%s\"\n", $2);*/
    if(Command::_currentCommand._outFile)
      yyerror("Ambiguous output redirect.\n");
    Command::_currentCommand._append = 1;
    Command::_currentCommand._outFile = $2;
  }
  | DOUBLEGREATAMP WORD{
    /*printf("   Yacc: append output and err \"%s\"\n", $2);*/
    if(Command::_currentCommand._outFile)
      yyerror("Ambiguous output redirect.\n");
    Command::_currentCommand._append = 1;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
  }
  ;

iomodifier_list:
  iomodifier_list iomodifier_opt
  | iomodifier_opt
  |
  ;

back_flag:
  AMP {
    Command::_currentCommand._background = 1;
  }
  | /* empty*/
  ;


pipe_line:
  pipe_line PIPE command_and_args
  | command_and_args
  ;

%%

void
yyerror(const char * s)
{
  Command::_currentCommand._err = 1;
  fprintf(stderr,"%s", s);
}

#if 0
main()
{
  yyparse();
}
#endif
