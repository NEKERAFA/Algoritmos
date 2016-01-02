

main.out: main.c utils.o sumasubmax.o
	gcc -g main.c utils.o sumasubmax.o -o main.out -lm

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -lm

sumasubmax.o: sumasubmax.h sumasubmax.c
	gcc -g -c sumasubmax.c -o sumasubmax.o 

clean: 
	rm *.o main.out