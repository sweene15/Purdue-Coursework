#include <stdarg.h>
#include <stdio.h>

extern void printx(int d);
extern void printd(int d);

//my printf function in C
int myprintf(const char *f, ...){
	int ptr_inc = 1;
	void* arg_ptr = &f + ptr_inc;
	//printf("%x\n", &f);
	//printf("%x\n", &arg_ptr);
	//printf("%x\n", arg_ptr);
	//printf("%d\n", *(int *)arg_ptr);
	//ptr_inc++;
	//arg_ptr = &f + ptr_inc;
	//printf("%d\n", *(int *)arg_ptr);
	//ptr_inc++;
	//arg_ptr = &f + ptr_inc;
	//printf("%c\n", *(char *)arg_ptr);
	//printf(
	while(*f){
		if(*f == '%'){
			//printf("ME SEE ARG");
			f++;
			if(!*f)
				break;
			if(*f == 'c'){
				putchar(*(char *)arg_ptr);
				ptr_inc++;
				arg_ptr = &f + ptr_inc;
			}
			if(*f == 's'){
				int count = 0;
				while(*(char *)(* (int *)arg_ptr + count) != '\0'){
					putchar(*(char *)(* (int *)arg_ptr + count));
					count++;
				}
				count = 0;
				ptr_inc++;
				arg_ptr = &f + ptr_inc;
			}
			if(*f == 'x'){
				//printf("ME SEE HEX");
				int i = (*(int *) arg_ptr);
				printx(i);
				ptr_inc++;
				arg_ptr = &f + ptr_inc;
			}
			if(*f == 'd'){
				int i = (*(int *)arg_ptr);
				printd(i);
				ptr_inc++;
				arg_ptr = &f + ptr_inc;
			}
			if(*f == '%'){
				printf("ME SEE EXIT");
			}
			f++;
			if(!*f)
				break;
		}
		putchar(*f);
		f++;
	}
}
