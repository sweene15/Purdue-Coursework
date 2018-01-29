CC = gcc
CFLAGS = -lm 
DEPS = header1.h
OBJ = read_vecs.o main.o calc_dist.o calc_sum.o calc_diff.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

distec: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) 
