mymain: main.o somefuncs.o run_func_double.o
	gcc -o mymain main.o somefuncs.o run_func_double.o
main.o: main.c header1.h
	gcc -c main.c
run_func_double.o: run_func_double.c header1.h
	gcc -c run_func_double.c
