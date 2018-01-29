// basic file I/O

#include <stdio.h>
#include <stdlib.h>

main() {

FILE *fp, *fp1;
int x[100], i, j;

  // open file to read
  fp = fopen("test.dat","r");
  if(fp == NULL) {
	fprintf(stderr,"file test.dat does not exist\n");
	exit(1);
  }

  // open file to write
  fp1 = fopen("output.dat","w");
  if(fp == NULL) {
	fprintf(stderr,"creating write file failed\n");
	exit(1);
  }

  // read data
  i = 0;
  while(fscanf(fp,"%d",&x[i]) != EOF) 
	i++;

  // write data
  for(j=0; j<i; j++)
  	fprintf(fp1,"%d\n",x[j]);

}
