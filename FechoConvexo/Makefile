CC=clang
CFLAGS=-Wall -Wextra -Werror -g -std=c99 -pipe

OBJECTS=fecho.o entrada.o benchmark.o brute_force.o
BINARY=./fechoconvexo

default: runValgrind

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

release: clean
	$(MAKE) $(MFLAGS) CC=cc CFLAGS=-O2\ -std=c99\ -ffast-math\ -march=native\ -pipe $(BINARY)
	$(BINARY) < entrada.in

runValgrind: $(BINARY) entrada.in
	valgrind --leak-check=full $(BINARY) < entrada.in

fecho.o: fecho.c entrada.h geometria.h algoritmos.h
	$(CC) $(CFLAGS) -c fecho.c

entrada.o: entrada.c entrada.h geometria.h
	$(CC) $(CFLAGS) -c entrada.c

benchmark.o: ../benchmark.c ../benchmark.h
	$(CC) $(CFLAGS) -c ../benchmark.c

brute_force.o: brute_force.c entrada.h algoritmos.h
	$(CC) $(CFLAGS) -c brute_force.c

clean:
	$(RM) $(BINARY) $(OBJECTS)

