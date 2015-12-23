/*
 * Práctica 1 - Suma de la subsecuencia máxima
 *
 * Autores:
 * - Rafael Alcalde Azpiazu
 * - Iván Anta Porto
 * - David Méndez Álvarez
 *
 * Creado el jue 10 sep 2015 08:48:10 (CEST)
 *
 * Suma de la subsecuencia máxima: Dados n números enteros a1, a2, ..., an,
 * encontrar el valor máximo de
 * j
 * ∑ ak con 1 ≤ i ≤ j ≤ n (por conveniencia, la suma de la subsecuencia máxima
 * k=i  es 0 si todos los enteros son negativos).
 *
*/

#include <stdio.h>
#include "sumasubmax.h"
#include "utils.h"

// Algoritmo 1
int sumaSubMax1( int v[], int n ) {
   int i, j, sumaMax = 0;
   for (i = 0; i < n; ++i) {
      int estaSuma = 0;
      for (j = i; j < n; ++j) {
         estaSuma = estaSuma + v[j];
         if (estaSuma > sumaMax) {
            sumaMax = estaSuma;
         }
      } // Fin segundo para
   } // Fin primer para
   return sumaMax;
}

// Algoritmo 2
int sumaSubMax2( int v[], int n ) {
   int estaSuma, sumaMax, j;
   estaSuma = 0;
   sumaMax = 0;
   for (j = 0; j < n; ++j) {
      estaSuma = estaSuma + v[j];
      if (estaSuma > sumaMax) {
         sumaMax = estaSuma;
      } else if (estaSuma < 0) {
         estaSuma = 0;
      }
   }
   return sumaMax;
}

// Test 1 con vectores definidos
void test1() {
   int v[][5] = { {-9,  2, -5, -4,  6},
                  { 4,  0,  9,  2,  5},
                  {-2, -1, -9, -7, -1},
                  { 9, -2,  1, -7, -8},
                  {15, -2, -5, -4, 16},
                  { 7, -5,  6,  7, -7} };
   int i;
   printf("Test 1\n");
   printf("%19s sumaSubMax1 sumaSubMax2\n", "");
   for(i = 0; i < 6; ++i) {
      mostrar_vector(v[i], 5);
      printf("%8d\t%8d\n", sumaSubMax1(v[i], 5), sumaSubMax2(v[i], 5));
   }
}

// Test 2 con vectores generados pseudoaleatoriamente
void test2() {
   const int tam = 9;
   const int nvect = 5;
   int v[nvect][tam];
   int i;
   for(i = 0; i < nvect; ++i) { aleatorio(v[i], tam); }
   printf("Test 2\n");
   printf("%30s sumaSubMax1 sumaSubMax2\n", "");
   for(i = 0; i < nvect; ++i) {
      mostrar_vector(v[i], tam);
      printf("%8d\t%8d\n", sumaSubMax1(v[i], tam), sumaSubMax2(v[i], tam));
   }
}

// Función para validar los algoritmos
void testear(){
   test1();
   test2();
}