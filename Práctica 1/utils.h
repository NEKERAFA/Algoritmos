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


// Se establece la semilla para una serie de enteros pseudoaleatorios
void inicializar_semilla();

// Obtiene la hora del sistema en microsegundos
double microsegundos();

// Se generan números pseudoaleatorios entre -n y+n
void aleatorio(int v[], int n);

// Muestra el contenido de un vector
void mostrar_vector ( int v[], int n );

//Realiza toda la medicion de tiempos
void tiempos();

#endif