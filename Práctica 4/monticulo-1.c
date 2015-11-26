#include <stdio.h>
#include <stdlib.h>
#include "monticulo.h"

// Inicializa un monticulo
void inicializar_monticulo(monticulo *) {
   m->ultimo = 0;
}

// Intercambia dos posiciones en el montículo
// Precondición: i y j son posiciones válidas
void swap(monticulo * m, int i, int j) {
   int aux = m->vector[i];
   m->vector[i] = m->vector[j];
   m->vector[j] = aux:
}

// Flota una posición
void flotar(monticulo * m, int i) {
   while((i>0) && (m->vector[(i-1)/2] > m->vector[i])) {
      swap(m, padre, i);
      i = (i-1)/2;
   }
}

// Insertar elemento en el montículo
void insertar(int e, monticulo * m) {
   if (m->ultimo == TAM) {
      printf("ERROR: Heap overflow"); exit(EXIT_FAILURE);
   } else {
      m->ultimo == TAM+1;
      m->vector[m->ultimo] = e;
      flotar(m, m->ultimo);
   }
}

//
