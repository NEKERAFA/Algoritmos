/*
 * Práctica 4 -
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha: 26/11/2015
 *
*/

#include <stdio.h>
#include "abb.h"
#include "utils.h"

int main(){
   inicializar_semilla();

   printf(" Se testean las diferentes funciones\n");
   testear();

   printf("\n\n Se miden diferentes tiempos de funciones\n\n");
   tiempos();

   return 0;
}
