# Makefile del shell

CC = gcc
CFLAGS = -g -Wall
OBJ_PRIN = principal.out
OBJ_ABB = abb.o
OBJ_UTILS = utils.o
OBJS = utils.o abb.o


all: abb utils
	echo -e '\e[32mCompilando terminal...\e[0m'
	$(CC) $(CFLAGS) principal.c  $(OBJS) -o $(OBJ_PRIN) -lm

abb: 
	echo -e '\e[32mCompilando funciones...\e[0m'
	rm -f abb.o
	$(CC) $(CFLAGS) -c abb.c

utils:
	echo -e '\e[32mCompilando utilidades...\e[0m'
	rm -f utils.o
	$(CC) $(CFLAGS) -c utils.c
