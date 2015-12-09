/*
 * Práctica 4 - Montículos
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha: 09/12/2015
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "monticulo.h"

// Inicializa un monticulo
void inicializar_monticulo(monticulo * m) {
   m->ultimo = -1;
}

// Intercambia dos posiciones en el montículo
// Precondición: i y j son posiciones válidas
void swap(monticulo * m, int i, int j) {
   int aux = m->vector[i];
   m->vector[i] = m->vector[j];
   m->vector[j] = aux;
}

// Flota una posición
void flotar(monticulo * m, int i) {
   while((i>0) && (m->vector[(i-1)/2] > m->vector[i])) {
      swap(m, (i-1)/2, i);
      i = (i-1)/2;
   }
}

// Insertar elemento en el montículo
void insertar(monticulo * m, int e){
   if (m->ultimo == TAM-1) {
      printf("ERROR: Heap overflow");
      exit(EXIT_FAILURE);
   } else {
      m->ultimo = m->ultimo+1;
      m->vector[m->ultimo] = e;
      flotar(m, m->ultimo);
   }
}

// Hunde una posición
void hundir(monticulo * m, int i) {
   int hi, hd;
   int j;

   do {
      hi = 2*i + 1;
      hd = 2*i + 2;
      j = i;

      if ((hd <= m->ultimo) && (m->vector[hd] < m->vector[i]))
         i = hd;

      if ((hi <= m->ultimo) && (m->vector[hi] < m->vector[i]))
         i = hi;

      swap(m, i, j);

   } while (j != i);
}

// Elimina el menor elemento del montículo y lo devuelve
int eliminar_menor(monticulo * m) {
   int x;

   if (m->ultimo == -1) {
      printf("ERROR: Empty heap");
      exit(EXIT_FAILURE);
   }
   else {
      x = m->vector[0];
      m->vector[0] = m->vector[m->ultimo];
      m->ultimo = m->ultimo - 1;

      if (m->ultimo > -1) {
         hundir(m, 0);
      }

      return x;
   }
}

// Crea un montículo a partir de un vector
void crear_monticulo(int v[], int n, monticulo * m) {
   int i;
   
   for (i = 0; i < n; i++) {
      m->vector[i] = v[i];
   }
   
   m->ultimo = n - 1;
   
   for (i = (n-1)/2; i >= 0; i--) {
      hundir(m, i);
   }
}

// Comprueba si un vector está ordenado
int esta_ordenado(int v[],int n){
   int i;

   for (i=0;i<(n-1);i++){ //Se recorre el vector
      if(v[i]>v[(i+1)]){ //Si el siguiente elemento es menor que el actual
         return 0; //El vector no está ordenado
      }
   }
   return 1;//Si no, el vector está ordenado
}

// Ordena un vector aplicando el algoritmo de ordenación por montículos
void ord_monticulo(int v[], int n) {
   monticulo m;
   int i;
   
   inicializar_monticulo(&m);
   crear_monticulo(v, n, &m);
   for (i = 0; i < n; i++) {
      v[i] = eliminar_menor(&m);
   }
}

void testinicializarmonticulo(){
   monticulo m;

   printf("Test inicializar_monticulo\n");
   inicializar_monticulo(&m);

   if(m.ultimo == -1){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testswap(){
   monticulo m;
   int valido = 1;

   printf("Test swap\n");

   inicializar_monticulo(&m);

   m.vector[0] = 4;
   m.vector[1] = 2;
   m.vector[2] = 3;
   m.vector[3] = 1;
   m.ultimo = 3;

   swap(&m,0,3);

   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 2) valido = 0;
   if(m.vector[2] != 3) valido = 0;
   if(m.vector[3] != 4) valido = 0;
   if(m.ultimo    != 3) valido = 0;
   
   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }

}

void testflotar(){
   monticulo m;
   int valido = 1;

   printf("Test flotar\n");
   inicializar_monticulo(&m);
   
   m.vector[0] = 2;
   m.vector[1] = 3;
   m.vector[2] = 4;
   m.vector[3] = 5;
   m.vector[4] = 6;
   m.vector[5] = 1;
   m.ultimo = 5;
   
   flotar(&m,5);
   
   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 3) valido = 0;
   if(m.vector[2] != 2) valido = 0;
   if(m.vector[3] != 5) valido = 0;
   if(m.vector[4] != 6) valido = 0;
   if(m.vector[5] != 4) valido = 0;
   if(m.ultimo    != 5) valido = 0;
   
   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testhundir(){
   monticulo m;
   int valido = 1;

   printf("Test hundir\n");
   inicializar_monticulo(&m);
   
   m.vector[0] = 6;
   m.vector[1] = 1;
   m.vector[2] = 2;
   m.vector[3] = 3;
   m.vector[4] = 4;
   m.vector[5] = 5;
   m.ultimo = 5;
   
   hundir(&m,0);
   
   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 3) valido = 0;
   if(m.vector[2] != 2) valido = 0;
   if(m.vector[3] != 6) valido = 0;
   if(m.vector[4] != 4) valido = 0;
   if(m.vector[5] != 5) valido = 0;
   if(m.ultimo    != 5) valido = 0;
   
   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testinsertar(){
   monticulo m;
   int valido = 1;

   printf("Test insertar\n");
   inicializar_monticulo(&m);

   insertar(&m,5);
   insertar(&m,3);
   insertar(&m,7);
   insertar(&m,0);
   insertar(&m,6);
   insertar(&m,8);
   insertar(&m,9);
   insertar(&m,2);
   insertar(&m,1);
   insertar(&m,4);

   if(m.vector[0]!=0) valido = 0;
   if(m.vector[1]!=1) valido = 0;
   if(m.vector[2]!=7) valido = 0;
   if(m.vector[3]!=2) valido = 0;
   if(m.vector[4]!=4) valido = 0;
   if(m.vector[5]!=8) valido = 0;
   if(m.vector[6]!=9) valido = 0;
   if(m.vector[7]!=5) valido = 0;
   if(m.vector[8]!=3) valido = 0;
   if(m.vector[9]!=6) valido = 0;
   if(m.ultimo != 9) valido = 0;

   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testeliminarmenor(){
   monticulo m;
   int valido = 1;

   printf("Test eliminar_menor\n");

   inicializar_monticulo(&m);

   insertar(&m,5);
   insertar(&m,3);
   insertar(&m,7);
   insertar(&m,0);
   insertar(&m,6);
   insertar(&m,8);
   insertar(&m,9);
   insertar(&m,2);
   insertar(&m,1);
   insertar(&m,4);

   if(eliminar_menor(&m)!=0) valido = 0;
   if(eliminar_menor(&m)!=1) valido = 0;
   if(eliminar_menor(&m)!=2) valido = 0;
   if(eliminar_menor(&m)!=3) valido = 0;
   if(eliminar_menor(&m)!=4) valido = 0;
   if(eliminar_menor(&m)!=5) valido = 0;
   if(eliminar_menor(&m)!=6) valido = 0;
   if(eliminar_menor(&m)!=7) valido = 0;
   if(eliminar_menor(&m)!=8) valido = 0;
   if(eliminar_menor(&m)!=9) valido = 0;
   if(m.ultimo != -1) valido = 0;
   
   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testcrearmonticulo(){
   monticulo m;
   int v[10] = {5,3,7,0,6,8,9,2,1,4};
   int valido = 1;

   printf("Test crear_monticulo\n");
   inicializar_monticulo(&m);

   crear_monticulo(v,10,&m);

   if(m.vector[0]!=0) valido = 0;
   if(m.vector[1]!=1) valido = 0;
   if(m.vector[2]!=7) valido = 0;
   if(m.vector[3]!=2) valido = 0;
   if(m.vector[4]!=4) valido = 0;
   if(m.vector[5]!=8) valido = 0;
   if(m.vector[6]!=9) valido = 0;
   if(m.vector[7]!=5) valido = 0;
   if(m.vector[8]!=3) valido = 0;
   if(m.vector[9]!=6) valido = 0;
   if(m.ultimo != 9) valido = 0;

   if(valido){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

void testordenacionmonticulo(){
   int v[10] = {5,3,7,0,6,8,9,2,1,4};

   printf("Test ordenacion monticulo\n");

   ord_monticulo(v,10);

   if(esta_ordenado(v,10)){
      printf("+++Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}


void testear(){
   testinicializarmonticulo();
   testswap();
   testflotar();
   testhundir();
   testinsertar();
   testeliminarmenor();
   testcrearmonticulo();
   testordenacionmonticulo();
}
