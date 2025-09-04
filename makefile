CFLAGS=-I.
DEPS = argHandler.h convolve.h fileHelper.h Matrix.h
OBJ = argHandler.o convolve.o fileHelper.o Matrix.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

CITS: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
