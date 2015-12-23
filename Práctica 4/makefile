main.out: principal.c monticulo.o utils.o
	gcc -g principal.c monticulo.o utils.o -o main.out -lm

monticulo.o: monticulo.c monticulo.h
	gcc -g -c monticulo.c -o monticulo.o

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -lm