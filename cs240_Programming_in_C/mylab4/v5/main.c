#include <stdlib.h>
#include <stdio.h>

main() {
 // Part 1, Parsing
 char s [500]; //Inputted String
 char r [500]; //Final/ Result String
 char t [500]; //Temp String
 char failMessage[] = "YOU HAVE FAAAAILLLEEDDD to input a correct URL";
 char httpOrNah[10]; //Used to hold part of the string (http/https) to determine if http or https
 int httpOrHttps; //Http = 0, Https = 1
 int i, slash; //i is used to increment, slash is used to determine if a forward slash is present, which is then used to locate the domain name tag (.com, .edu, etc)
  // Recieve Input
  scanf("%s", s);
  printf("Inputted: %s\n", s);
  //HTTP, HTTPS or nah?
   //Copy Input String to Temp String
   for(i = 0;i < 500; i++) {
    t[i] = s[i];
   }
   //Determine if valid
   //Check if it is http
   if((t[0] == 'h' || t[0] == 'H') && (t[1] == 't' || t[1] == 'T') && (t[2] == 't' || t[2] == 'T') && (t[3] == 'p' || t[3] == 'P') && (t[4] == ':') && (t[5] == '/') && (t[6] == '/'))
    httpOrHttps = 0;
   //If not, check for https
   else if((t[0] == 'h' || t[0] == 'H') && (t[1] == 't' || t[1] == 'T') && (t[2] == 't' || t[2] ==  'T') && (t[3] == 'p' || t[3] == 'P') && (t[4] == 's' || t[4] == 'S') && (t[5] == ':') && (t[6] == '/') && (t[7] == '/'))
    httpOrHttps = 1;
   //If its neither, invalid.
   else
    {
    printf("%s\nHTTP CHECK FAILED\n", failMessage);
    return -1;
    }
   //Cut temp String based upon httpOrHttps
   if(httpOrHttps == 0)
    for(i = 0; i < 400; i++) {
      t[i] = t[i + 7];
    }
   else if(httpOrHttps == 1)
    for(i = 0; i < 400; i++) {
      t[i] = t[i + 8];
     }
   //Check for 'www.'
   if(!((t[0] == 'w' || t[0] == 'W') && (t[1] == 'w' || t[1] == 'W') && (t[2] == 'w' || t[2] == 'W') && (t[3] == '.')))
    {
    printf("%s\nWWW CHECK FAILED\n", failMessage);
    return -1;
    }
   //Search for /, indicating .xxx is right before it.
   for(i = 0; i < 400; i++) {
    if(t[i] == '/'|| t[i] == '\0'){
     slash = i;
     i = 401;
     }
    }
   //Check for .com or .edu
   if(!(((t[slash - 1] == 'm' || t[slash - 1] == 'M') && (t[slash - 2] == 'o' || t[slash - 2] == 'O') && (t[slash - 3] == 'c' || t[slash - 3] == 'C') && (t[slash - 4] == '.')) || ((t[slash - 1] == 'u' || t[slash - 1] == 'U') && (t[slash - 2] == 'd' || t[slash - 2] == 'D') && (t[slash - 3] == 'e' || t[slash - 3] == 'E') && (t[slash - 4] == '.'))))
    {
     printf("%s\nCOMorEDU CHECK FAILED\n", failMessage);
     return -1;
    }
   //At this point, URL should be valid. 
   //Now, make all chars lowercase
   for(i = 0; i < 500; i++) {
    if(65 <= s[i] && s[i] <=90) {
     s[i] = s[i] + 32;
    }
   }
   //Print
   printf("Converted: %s\n", s);
 //Part 2
 //Modify string t (Which already has http cut out), and put in result string r
   r[0] = 'h';
   r[1] = 'o';
   r[2] = 's';
   r[3] = 't';
   r[4] = ' ';
   for(i = 0; i < 400; i++) {
    r[i + 5] = t[i];
    }
 //Count valid chars
 int charCount = 5;
 for(i = 5; i < 400; i++) {
  if(r[i] != ' ' && r[i] != '\0')
   charCount ++;
  else
   i = 500;
 }
 //String still has nulls in it, so use charCount to generate a new string
 char f [charCount];
 for(i = 0; i < charCount; i++) {
   f[i] = r[i];
 }
 //run system(), which prints IP and all that jazz
 system(f);
}

