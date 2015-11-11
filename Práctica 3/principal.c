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

#include <stdio.h>
#include "abb.h"
#include "utils.h"

int main(){
   int i;

   inicializar_semilla();

   printf(" Se testean las diferentes funciones\n");
   testear();

   printf("\n\n Se miden diferentes tiempos de funciones\n\n");
   for (i = 0; i < 3; i++) tiempos();

   return 0;
}
