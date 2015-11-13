/*
 * Práctica 3 -
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha: 11/11/2015
 *
*/

#include "abb.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a>b) ? (a) : (b))
#define MIN(a, b) ((a<b) ? (a) : (b))

static struct nodo  *crearnodo(int e) {
   struct nodo *p = malloc(sizeof(struct nodo));
   if (p == NULL) {
      printf("memoria agotada\n"); exit(EXIT_FAILURE);
   }
   p->elem = e;
   p->num_repeticiones = 1;
   p->izq = NULL;
   p->der = NULL;
   return p;
}

arbol insertar(int e, arbol a){
   if (a == NULL)
      return crearnodo(e);
   else if (e < a->elem)
      a->izq = insertar(e, a->izq);
   else if (e > a->elem)
      a->der = insertar(e, a->der);
   else
      a->num_repeticiones++;
   return a;
}

arbol creararbol(){
   return NULL;
}

int esarbolvacio(arbol a){
   return a == NULL;
}

arbol eliminararbol(arbol a){
   if (a != NULL){
      a->izq = eliminararbol(a->izq);
      a->der = eliminararbol(a->der);
      free(a);
   }
   return NULL;
}

void visualizar(arbol a){
   if (a!=NULL){
      printf("(");
      if(a->izq != NULL){
         visualizar(a->izq);
      }
      printf(" %d ",a->elem);
      if(a->der != NULL){
         visualizar(a->der);
      }
      printf(")");
   } else {
      printf("()");
   }
}

// Precondición: el árbol no es nulo
posicion hijoizquierdo(arbol a) {
   return a->izq;
}

// Precondición: el árbol no es nulo
posicion hijoderecho(arbol a) {
   return a->der;
}

// Precondición: el árbol no es nulo
int elemento(posicion p) {
   return p->elem;
}

// Precondición: el árbol no es nulo
int numerorepeticiones(posicion p) {
   return p->num_repeticiones;
}

posicion buscar(int e, arbol a) {
   if ((a == NULL) || (a->elem == e)) return a;
   else if (a->elem > e) return buscar(e, a->izq);
   else return buscar(e, a->der);
}

int altura(arbol a) {
   if (a == NULL) return -1;
   return (1+MAX(altura(a->izq), altura(a->der)));
}

arbol vectortotree(arbol a, int v[], int n) {
   int i;
   for(i = 0; i<n; i++) a = insertar(v[i], a);
   return a;
}

void testcreararbol(){
   arbol a;

   printf("\nTest creararbol\n");

   a = creararbol();
   if (a == NULL) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }
}

void testesarbolvacio(){
   arbol a,b;
   printf("\nTest esarbolvacio\n");

   a = creararbol();
   b = creararbol();
   b = crearnodo(1);

   if (!esarbolvacio(b)&& esarbolvacio(a)) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(b);
}

void testinsertar(){
   arbol a;
   int superado = 1;

   printf("\nTest insertar\n");
   a = creararbol();
   printf("Insercion de 2,1,3\n");
   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   if(a->elem == 2){
      printf(" he insertado el 2\n");
   } else {
      superado = 0;
   }
   if(a->izq->elem == 1) {
      printf(" he insertado el 1\n");
   } else {
      superado = 0;
   }
   if(a->der->elem == 3) {
      printf(" he insertado el 3\n");
   } else{
      superado = 0;
   }

   if (superado) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}

void testvisualizar(){
   arbol a;
   char * vacia = "()";
   char * novacia = "(( 1 ) 2 ( 3 ))";

   printf("\nTest visualizar\n");

   a = creararbol();
   printf("Lista vacia:\n");
   printf("Resultado esperado : %s\n",vacia);
   printf("Resultado obtenido :");
   visualizar(a);
   printf("\n");

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   printf("Lista no vacia:\n");
   printf("Resultado esperado : %s\n",novacia);
   printf("Resultado obtenido :");
   visualizar(a);
   printf("\n");

   free(a->izq);
   free(a->der);
   free(a);
}
void testhijoizquierdo(){
   arbol a;
   posicion hi;

   printf("\nTest hijoizquierdo\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);
   hi = hijoizquierdo(a);

   if (hi->elem == 1) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testhijoderecho(){
   arbol a;
   posicion hd;
   printf("\nTest hijoderecho\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   hd = hijoderecho(a);

   if (hd->elem == 3) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testbuscar(){
   arbol a;

   printf("\nTest buscar\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   if ((buscar(1,a)!=NULL)&&(buscar(2,a)!=NULL)&&(buscar(3,a)!=NULL)&&((buscar(4,a)==NULL))) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testelemento(){
   arbol a;

   printf("\nTest elemento\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   if ((elemento(a)==2)&&(elemento(a->izq)==1)&&(elemento(a->der)==3)) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testaltura(){
   arbol a;
   int i;
   printf("\nTest altura\n");
   a = creararbol();

   i = altura(a);

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   if ((i == -1)&&(altura(a->izq)==0)&&(altura(a)==1)) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testnumerorepeticiones(){
   arbol a;

   printf("\nTest numerorepeticiones\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(2,a);

   if ((numerorepeticiones(a)==2)&&(numerorepeticiones(a->izq)==1)) {
      printf("Test Superado\n");
   } else {
      printf("******** TEST FALLADO ********\n");
   }

   free(a->izq);
   free(a->der);
   free(a);
}
void testeliminararbol(){
   arbol a;
   printf("\nTest eliminararbol\n");
   a = creararbol();

   a = insertar(2,a);
   a = insertar(1,a);
   a = insertar(3,a);

   visualizar(a);
   printf("\n");

   a = eliminararbol(a);

   visualizar(a);
   printf("\n");
}

void testvectortotree() {
   arbol a;
   int v[100000];
   int i;

   printf("\nTest vectortotree\n");

   printf("Vector: ");
   for (i=0; i<5; i++) {
      v[i] = (rand() % 10) - 5;
      printf("%i ", v[i]);
   }
   printf("\n");

   a = creararbol();
   a = vectortotree(a, v, 5);
   visualizar(a);

   a = eliminararbol(a);
}

void testear(){
   testcreararbol();
   testesarbolvacio();
   testinsertar();
   testvisualizar();
   testhijoizquierdo();
   testhijoderecho();
   testbuscar();
   testelemento();
   testaltura();
   testnumerorepeticiones();
   testeliminararbol();
   testvectortotree();

   printf("\n");
}

void buscarvector(arbol a, int v[], int n) {
   int i;
   for(i = 0; i<n; i++) buscar(v[i], a);
}

void tiempos() {
   double v[8][3];
   printf("%10s %10s %10s\n", "n", "t_ins(n)", "t_bus(n)");
   medir_tiempos(v);
   medicion_insercion(v);
   medicion_busqueda(v);
}
