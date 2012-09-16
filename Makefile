CC=clang
CFLAGS=-Wall

FECHOCONVEXO_OBJECTS=fecho.o entrada.o benchmark.o

default: FechoConvexo

FechoConvexo: $(FECHOCONVEXO_OBJECTS)
	$(CC) $(LDFLAGS) $(FECHOCONVEXO_OBJECTS) -o FechoConvexo

FechoConvexoValgrind: FechoConvexo
	valgrind --leak-check=full ./FechoConvexo < entrada.in

fecho.o: fecho.c entrada.h geometria.h
	$(CC) $(CFLAGS) -c fecho.c

entrada.o: entrada.c entrada.h geometria.h
	$(CC) $(CFLAGS) -c entrada.c

benchmark.o: benchmark.c benchmark.h
	$(CC) $(CFLAGS) -c benchmark.c

clean:
	$(RM) ./FechoConvexo $(FECHOCONVEXO_OBJECTS)

