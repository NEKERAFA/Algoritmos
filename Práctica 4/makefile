#Makefile de la práctica 4 de Algoritmos

CC = gcc
CFLAGS = -g -Wall

run: principal.out utils.o #Faltan cosas
	valgrind ./principal.out

principal.out: utils.o principal.c #Faltan cosas
	$(CC) $(CFLAGS) utils.o principal.c -o principal.out -lm

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c utils.h -o utils.o