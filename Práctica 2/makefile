
main.out: main.c ordenacion.o utils.o 
	gcc -g main.c ordenacion.o utils.o -o main.out -lm

ordenacion.o: ordenacion.h ordenacion.c
	gcc -g -c ordenacion.c -o ordenacion.o 

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -lm

clean: 
	rm *.o main.out