CC=clang
CFLAGS=-Wall -Wextra -Werror -g -std=c99 -pipe
LDFLAGS=-lm

OBJECTS=fecho.o input.o benchmark.o brute_force.o mean.o
BINARY=./fechoconvexo

default: runValgrind

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

release: clean
	$(MAKE) $(MFLAGS) CC=cc CFLAGS=-O2\ -std=c99\ -ffast-math\ -march=native\ -pipe\ -DNDEBUG $(BINARY)
	$(BINARY) < input.in

runValgrind: $(BINARY) input.in
	valgrind --leak-check=full $(BINARY) < input.in

fecho.o: fecho.c input.h geometry.h algorithm.h ../benchmark.h ../mean.h
	$(CC) $(CFLAGS) -c fecho.c

input.o: input.c input.h geometry.h
	$(CC) $(CFLAGS) -c input.c

benchmark.o: ../benchmark.c ../benchmark.h
	$(CC) $(CFLAGS) -c ../benchmark.c

brute_force.o: brute_force.c input.h algorithm.h
	$(CC) $(CFLAGS) -c brute_force.c

mean.o: ../mean.c ../mean.h
	$(CC) $(CFLAGS) -c ../mean.c

clean:
	$(RM) $(BINARY) $(OBJECTS)

