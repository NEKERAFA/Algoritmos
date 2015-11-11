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

#ifndef __ABB_ALG
#define __ABB_ALG

struct nodo {
   int elem;
   int num_repeticiones;
   struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

arbol insertar(int e, arbol a);
arbol creararbol();
int esarbolvacio(arbol a);
posicion buscar(int e, arbol a);
arbol eliminararbol(arbol a);
posicion hijoizquierdo(arbol a);
posicion hijoderecho(arbol a);
int elemento(posicion p);
int numerorepeticiones(posicion p);
int altura(arbol a);
void visualizar(arbol a);
arbol vectortotree(arbol a, int v[], int n);
void buscarvector(arbol a, int v[], int n);
void testear();
void tiempos();

#endif
