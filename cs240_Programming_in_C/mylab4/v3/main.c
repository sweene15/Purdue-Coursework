// basic file I/O

#include <stdio.h>
#include <stdlib.h>

main() {

FILE *fp;
int x, y, z;

  // open file to read
  fp = fopen("test.dat","r");
  // open failed
  if(fp == NULL) {
	fprintf(stderr,"file test.dat does not exist\n");
	exit(1);
  }

  fscanf(fp,"%d %d %d",&x,&y,&z);
  fprintf(stdout,"%d %d %d\n",x,y,z);

}
