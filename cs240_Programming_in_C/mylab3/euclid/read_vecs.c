#include "header1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int read_vecs(int *vecSize, double *x, double *y) {

char inputDimension[100];
char inputVector1[100];
char inputVector2[100];
char* comp[100];
char* comp2[100];
char* comp3[100];
char *token, *token2, *token3;
char tempChar;
int tempInt;
int i, j, k, l, m;

 //Get First Row of Input
 scanf(" %500[0-9a-zA-Z ]", inputDimension);
 //Split into Tokens, put in array
 i = 0;
 token = strtok(inputDimension, " ");
 while(token != NULL) {
   comp[i] = malloc(strlen(token) +1);
   strcpy(comp[i], token);
   token = strtok(NULL, " ");
   i++;
 }
 //Convert and set Vecsize
 tempChar = *comp[1];
 tempInt = tempChar;
 if(48 <= tempInt && tempInt <= 57) {
  tempInt = tempInt - 48;
  vecSize = &tempInt;
  printf("vecSize: %d\n", *vecSize);
 } else {
  return -1;
 }
 //Get Second Row of Input
 scanf(" %500[0-9a-zA-Z ]", inputVector1);
 //Split into tokens, put in array
 j = 0;
 token2 = strtok(inputVector1, " ");
 while(token2 != NULL) {
   comp2[j] = malloc(strlen(token2) +1);
   strcpy(comp2[j], token2);
   token2 = strtok(NULL, " ");
   j++;
 }
 //Convert and set Vector 1
 l = 1; 
 while(l <= *vecSize) {
  x[l-1] = atof(comp2[l]);
  printf("%f\n", x[l-1]);
  l++;
 }
 //Get Third Row of Input
 scanf(" %500[0-9a-zA-Z ]", inputVector2);
 //Split into tokens, put in array
 k = 0;
 token3 = strtok(inputVector2, " ");
 while(token3 != NULL) {
   comp3[k] = malloc(strlen(token3) +1);
   strcpy(comp3[k], token3);
   token3 = strtok(NULL, " ");
   k++;
 }
 //Convert and set Vector 2
 m = 1; 
 while(m <= *vecSize) {
  y[m-1] = atof(comp3[m]);
  printf("%f\n", y[m-1]);
  m++;
 }
 printf("vecSize: %d\n", *vecSize); 
 return 1;
}
