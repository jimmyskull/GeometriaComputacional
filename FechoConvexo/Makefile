CC=clang
CFLAGS=-Wall -Wextra -g -std=c99 -pipe
LDFLAGS=-lm

OBJECTS=fecho.o input.o benchmark.o brute_force.o mean.o gift_wrapping.o \
	rbtree.o insertion_hull.o
BINARY=./fechoconvexo

default: runValgrind

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

release: clean
	$(MAKE) $(MFLAGS) CC=cc CFLAGS=-O3\ -march=native\ -std=c99\ -ffast-math\ -pipe\ -DNDEBUG $(BINARY)
	$(BINARY) < input.in

runValgrind: $(BINARY) input.in
	valgrind --leak-check=full $(BINARY) < input.in

fecho.o: fecho.c input.h geometry.h algorithm.h ../benchmark.h ../mean.h
	$(CC) $(CFLAGS) -c fecho.c

input.o: input.c input.h geometry.h
	$(CC) $(CFLAGS) -c input.c

benchmark.o: ../benchmark.c ../benchmark.h
	$(CC) $(CFLAGS) -c ../benchmark.c

brute_force.o: brute_force.c input.h algorithm.h geometry.h
	$(CC) $(CFLAGS) -c brute_force.c

gift_wrapping.o: gift_wrapping.c algorithm.h input.h geometry.h
	$(CC) $(CFLAGS) -c gift_wrapping.c

mean.o: ../mean.c ../mean.h
	$(CC) $(CFLAGS) -c ../mean.c

rbtree.o: rbtree.c rbtree.h
	$(CC) $(CFLAGS) -c rbtree.c

insertion_hull.o: insertion_hull.c algorithm.h rbtree.h input.h geometry.h
	$(CC) $(CFLAGS) -c insertion_hull.c

clean:
	$(RM) $(BINARY) $(OBJECTS) *.gch

