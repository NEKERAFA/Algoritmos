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
#include <stdio.h>
#include "utils.h"
#include "ordenacion.h"

// Función principal
void main(){
   int i;
   
   //Se inicializa la semilla para permitir la generación pseudoaleatoria de valores
   inicializar_semilla();

   printf("TEST DE LOS ALGORITMOS\n\n\n");

   //Se validan los algoritmos
   testear();

   printf("\n\n\n");
   printf("MEDICION DE TIEMPOS\n\n\n");
   //Se realizan todas las mediciones 4 veces para intentar evitar mediciones anómalas en la medida de lo posible
   for(i = 0;i<4;i++){
      //Se miden los tiempos
      tiempos();
   }
}