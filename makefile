#
#  CITS 5507 2025 S2
#  Jared Healy (23398223)
#

CC=mpicc
CFLAGS=-I. -fopenmp -O3
DEPS = argHandler.h convolve.h Matrix.h
OBJ = argHandler.o convolve.o Matrix.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

CITS: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
