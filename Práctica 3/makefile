main.out: principal.c utils.o abb.o
	gcc -g principal.c utils.o abb.o -o main.out -lm

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -lm

abb.o: abb.h abb.c
	gcc -g -c abb.c -o abb.o 
