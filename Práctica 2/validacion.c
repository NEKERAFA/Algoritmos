#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

//Definición de cabeceras
//Algoritmos implementados:
void ord_ins(int v[], int n);
void ord_shell(int v[], int n);

//Funciones para testear los algoritmos:
void test (void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),
   int n);
void testear();

//Funciones para realizar la medición de tiempos
//void medir_tiempos();

//Funciones de inicialización de vectores
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);

//otras utilidades
void inicializar_semilla();
int esta_ordenado(int v[],int n);
void listar_vector( int v[], int n );
//double tiempo_promedio();
//void mostrar_tiempo()

//Implementación de las funciones:
void inicializar_semilla() {
   srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudo aleatorio entre -n y +n */
   int i, m=2*n+1;
   for (i=0; i < n; i++)
      v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
   int i;
   for (i=0; i < n; i++)
      v[i] = i;
}

void descendente(int v [], int n){
   int i,j = (n-1);
   for (i=0; i < n; i++)
      v[i] = j--;
      
}

int esta_ordenado(int v[],int n){
   int i;
   for (i=0;i<(n-1);i++){
      if(v[i]>v[i+1]){
         return 0;
      }
   }
   return 1;
}
// Lista los vectores
void listar_vector( int v[], int n ) {
	int i;
	printf("[ ");
	for (i = 0; i < n; ++i) {
		printf("%3d ", v[i]);
	}
	printf("]\n");
}

void test (void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),int n){
   int v[n];
   
   printf("Se inicializa el vector \n");
   inicializar(v,n);

   listar_vector(v,n);

   if(esta_ordenado){
      printf("El vector está ordenado \n");
   } else {
      printf("El vector NO está ordenado\n");
   }

   printf("Se procede a ordenar el vector \n");
   ordenar(v,n);
   
   listar_vector(v,n);

   if(esta_ordenado){
      printf("TEST SUPERADO \n");   
   } else {
      printf("TEST FALLADO\n");   
   }
}

/*Los algoritmos deben superar 3 casos de entrada distinta, que esté ordenada ascendentemente, descendentemente y que este desordenada */

void testear(){
   int n = 10;   
   printf("Test de Ordenación por insercion con vector ordenado ascendentemente \n \n");
   test(&ord_ins,&ascendente,n);

   printf("Test de Ordenación por insercion con vector ordenado descendentemente \n \n");
   test(&ord_ins,&descendente,n);

   printf("Test de Ordenación por insercion con el vector desordenado \n \n");
   test(&ord_ins,&aleatorio,n);

   printf("Test de Ordenación de shell con vector ordenado ascendentemente \n \n");
   test(&ord_shell,&ascendente,n);

   printf("Test de Ordenación de shell con vector ordenado descendentemente \n \n");
   test(&ord_shell,&descendente,n);

   printf("Test de Ordenación de shell con el vector desordenado \n \n");
   test(&ord_shell,&aleatorio,n);
}

void main(){
   testear();
}
