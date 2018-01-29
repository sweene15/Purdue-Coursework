#include <stdio.h>
#include <string.h>

int readinput(char *c){ 
//Take in input
  scanf("%s", c);
//Check for 'ne'
     if(c[0] == 'n' && c[1] == 'e' && c[2] == '\0') 
         return 0;
//Check for 'oxi'
     else if(c[0] == 'o' && c[1] == 'x' && c[2] == 'i' && c[3] == '\0')
         return 1;
//If neither work, return that it cannot be translated.
     else
         return -1;
}
