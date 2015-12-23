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
#ifndef __UTILS_ALG_
#define __UTILS_ALG_

//Número de ejecuciones para el caso de tiempos menores a 500 microsegundos
#define K 1000  

// SELECTOR DE DIVISORES PARA LAS COTAS:
#define CONST 0
#define LOGN 1
#define LINEAL 2 
#define NLOGN 3
#define NEXP 4
#define N2LOGN 5


//Función que inicializa la semilla de generación de números pseudo aleatorios
void inicializar_semilla();
//Se generan números pseudo aleatorios entre -n y +n
void aleatorio(int v [], int n);
//Se inicializa el vector ascendentemente
void ascendente(int v [], int n);
//Se inicializa el vector descendentemente
void descendente(int v [], int n);
// Función que muestra todo el contenido de un vector
void listar_vector( int v[], int n );
//Función que comprueba si un vector está ordenado
int esta_ordenado(int v[],int n);
//Función que sirve para realizar la medición de los tiempos de los algoritmos en todos los casos
void tiempos();
#endif