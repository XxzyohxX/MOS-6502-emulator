PROGRAM=salida
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all: $(PROGRAM)

$(PROGRAM):direccionamiento.o operaciones.o status.o tda.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) direccionamiento.o operaciones.o status.o tda.o main.o -o $(PROGRAM)

direccionamiento.o: direccionamiento.c tda.h status.h operaciones.h direccionamiento.h diccionario.h
	$(CC) $(CFLAGS) -c  direccionamiento.c

operaciones.o: operaciones.c tda.h status.h operaciones.h direccionamiento.h diccionario.h
	$(CC) $(CFLAGS) -c  operaciones.c

status.o: status.c tda.h status.h operaciones.h direccionamiento.h diccionario.h
	$(CC) $(CFLAGS) -c  status.c

tda.o: tda.c tda.h status.h operaciones.h direccionamiento.h diccionario.h
	$(CC) $(CFLAGS) -c  tda.c

main.o: main.c tda.h status.h operaciones.h direccionamiento.h diccionario.h
	$(CC) $(CFLAGS) -c  main.c

.PHONY: clean
clean:
	rm -vf  *.o $(PROGRAM)
