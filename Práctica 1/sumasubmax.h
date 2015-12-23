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

#ifndef __SUMASUBMAX_ALG_
#define __SUMASUBMAX_ALG_

// Algoritmo 1
int sumaSubMax1( int v[], int n );

// Algoritmo 2
int sumaSubMax2( int v[], int n );

// Función para validar los algoritmos
void testear();
#endif