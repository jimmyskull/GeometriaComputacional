CC=clang
CFLAGS=-Wall -Wextra -Werror -g -std=gnu99 -pipe

OBJECTS=fecho.o entrada.o benchmark.o
BINARY=./fechoconvexo

default: runValgrind

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

release: clean
	$(MAKE) $(MFLAGS) CC=cc CFLAGS=-O2\ -ffast-math\ -march=native\ -pipe

runValgrind: $(BINARY) entrada.in
	valgrind --leak-check=full $(BINARY) < entrada.in

fecho.o: fecho.c entrada.h geometria.h
	$(CC) $(CFLAGS) -c fecho.c

entrada.o: entrada.c entrada.h geometria.h
	$(CC) $(CFLAGS) -c entrada.c

benchmark.o: ../benchmark.c ../benchmark.h
	$(CC) $(CFLAGS) -c ../benchmark.c

clean:
	$(RM) $(BINARY) $(OBJECTS)

