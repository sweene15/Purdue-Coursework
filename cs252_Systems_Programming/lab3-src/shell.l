
/*
 *
 * CS-252 Fall 2017
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <cstring>
#include "y.tab.hh"


int mygetc(FILE * f){
  return getc(f);
}
#undef getc
#define getc(f) mygetc(f)
/*
ar * read_line();

int mygetc(FILE * f) {
static char *p;
char ch;

if (!isatty(0)) {
 // stdin is not a tty. Call real getc
 return getc(f);
}

// stdin is a tty. Call our read_line.

if (p==NULL || *p == 0) {
 char * s = read_line();
 p = s;
}

ch = *p;
p++;

return ch;
}

#undef getc
#define getc(f) mygetc(f)

*/
/*
static  void yyunput (int c,char *buf_ptr  );

void myunputc(int c) {
  unput(c);
}
*/

%}

%%


\n {
  return NEWLINE;
}

[ \t] {
  /* Discard spaces and tabs */
}

">" {
  return GREAT;
}

"<" {
  return LESS;
}

"2>" {
  return TWOGREAT;
}

">&" {
  return GREATAMP;
}

">>" {
  return DOUBLEGREAT;
}

">>&" {
  return DOUBLEGREATAMP;
}

"&" {
  return AMP;
}

"|"  {
  return PIPE;
}

["][^"\n]*["\n] {
  yylval.string_val = strdup(yytext + 1);
  if(yylval.string_val[yyleng-2] == '"')
    yylval.string_val[yyleng-2] = 0;
  return WORD;

}
[^ ^\\&<>|\t\n]*([\\][\\&<>|\t\n])*  {
  /* Assume that file names have only alpha chars */
  yylval.string_val = strdup(yytext);
  return WORD;
}



%%
