#include "abb.h"
#include <stdio.h>
#include "utils.h"

static struct nodo *crearnodo(int e) {
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
   if(a!=NULL){
      if(a->izq != NULL){
         eliminararbol(a->izq);
      }
      if(a->der !=NULL){
         eliminararbol(a->der);
      }
      free(a);
      a=NULL;
   }

   return a;
} 

void visualizar(arbol a){
   if (a!=NULL){
      printf("( ");
      if(a->izq != NULL){
         visualizar(a->izq);
      }
      printf(" %d ",a->elem);
      if(a->der != NULL){
         visualizar(a->der);
      }
      printf(" )")
   } else {
      printf("()");
   }
}


void testear(){
   int i,validacion = 1;
   arbol a;
   posicion p;

   printf("\n Testeo de las funciones \n");
   a = creararbol();
   if (a != NULL) validacion = 0;
   if (!esarbolvacio(a)) validacion = 0;
   if (altura(a)!=-1) validacion = 0;
   if (buscar(1,a)!=NULL) validacion = 0;
   visualizar (a);
   if(eliminararbol(a)!=NULL) validacion = 0;
   printf("Insercion de: 3, 1, 2 , 5, 4, 5 \n");
   if(insertar(3, a)==NULL) validacion = 0;
   if(altura(a)!=0)validacion = 0;
   if(insertar(1, a)==NULL) validacion = 0;
   if(insertar(2, a)==NULL) validacion = 0;
   if(insertar(5, a)==NULL) validacion = 0;
   if(insertar(4, a)==NULL) validacion = 0;
   if(insertar(5, a)==NULL) validacion = 0;
   if(esarbolvacio(a)==NULL) validacion = 0;
   if(buscar(3,a)!=a) validacion = 0
   visualizar(a);
   for(i=1;i<7;i++){
      printf("Busco %d y ",i);
      if((p=buscar(i,a))==NULL){
         printf("no encuentro nada");
      }else{
         printf("encuentro %d repetido %d veces",elemento(p),numerorepeticiones(p));
      }
   }
   if (altura(a)!=2) validacion = 0;
   if(hijoizquierdo(a)->elem != 1) validacion = 0;
   if(hijoderecho(a)->elem != 5) validacion = 0;
   if (eliminararbol(a)!=NULL) validacion = 0;
   if (validacion){
      printf("+++ Test Superado +++");
   }else{
      printf("*************Test Fallado*************");
   }   
}