/*
 * Práctica 2 - Algoritmos de Ordenación
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha: 20/10/2015
 *
 * Para esta práctica se van a implementar, validar y utilizar dos algoritmos 
 * de ordenación. Concretamente ordenación por inserción y ordenación shell.
 *
*/
#include "ordenacion.h"
#include "utils.h"

//Algoritmo de ordenación por shell
void ord_shell( int v[], int n ) {
   int incremento = n;
   int i, tmp, j, seguir;

   do {
      incremento = incremento/2;
      for(i = incremento; i < n ; i++) {
         tmp = v[i]; j = i; seguir = 1;
         while (((j-incremento) > -1) && seguir) {
            if(tmp < v[j-incremento]) {
               v[j] = v[j-incremento];
               j = j-incremento;
            } else { seguir = 0; }
         }
         v[j] = tmp;
      }
   } while (incremento > 1);
}

// Algoritmo de ordenación por inserción
void ord_ins (int v[], int n) {
   int i, j, x;

   for (i = 1; i < n; i++) {
      x = v[i];
      j = i - 1;
      while ((j > -1) && (v[j] > x)) {
         v[j + 1] = v[j];
         j--;
      }
      v[j + 1] = x;
   }
}

// Función para testear los algoritmos
void test (void (*ordenar)(int v[],int n),void (*inicializar)
      (int v[],int n),int n){
   int v[n];
   
   printf("·Se inicializa el vector\n");
   inicializar(v,n);

   listar_vector(v,n);

   printf("·Se procede a ordenar el vector: \n");
   ordenar(v,n);
   
   listar_vector(v,n);

   if(esta_ordenado(v,n)){
      printf("\nTEST SUPERADO \n");   
   } else {
      printf("\n************TEST FALLADO************\n");   
   }
}

// Se testean los algoritmos en 3 casos de entrada: que el vector ya esté 
// ordenado, que esté ordenado inversamente y que esté desordenado
void testear(){
   int n = 10;   

   printf("\n+++Test de Ordenación por insercion con vector ordenado ascendentemente \n \n");
   test(&ord_ins,&ascendente,n);

   printf("\n+++Test de Ordenación por insercion con vector ordenado descendentemente \n \n");
   test(&ord_ins,&descendente,n);

   printf("\n+++Test de Ordenación por insercion con el vector desordenado \n \n");
   test(&ord_ins,&aleatorio,n);

   printf("\n+++Test de Ordenación de shell con vector ordenado ascendentemente \n \n");
   test(&ord_shell,&ascendente,n);

   printf("\n+++Test de Ordenación de shell con vector ordenado descendentemente \n \n");
   test(&ord_shell,&descendente,n);

   printf("\n+++Test de Ordenación de shell con el vector desordenado \n \n");
   test(&ord_shell,&aleatorio,n);
}