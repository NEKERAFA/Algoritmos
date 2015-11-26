#Makefile de la práctica 4 de Algoritmos

CC = gcc
CFLAGS = -g -Wall

run: principal.out utils.o monticulo.o #Faltan cosas
	valgrind ./principal.out

principal.out: utils.o principal.c monticulo.o #Faltan cosas
	$(CC) $(CFLAGS) utils.o monticulo.o principal.c -o principal.out -lm

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

monticulo.o: monticulo.c monticulo.h
	$(CC) $(CFLAGS) -c monticulo.c -o monticulo.o

clear:
	rm -f principal.out utils.o monticulo.o