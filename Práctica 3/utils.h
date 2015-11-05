/*
 * Práctica 3 -
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha:
 *
*/
#ifndef __UTILIDADES_ALG
#define __UTILIDADES_ALG
//Número de ejecuciones para el caso de tiempos menores a 500 microsegundos
#define K 1000  

// SELECTOR DE DIVISORES PARA LAS COTAS:
#define CONST 0
#define LOGN 1
#define LINEAL 2 
#define NLOGN 3
#define NEXP 4
#define N2LOGN 5

//Definición de cabeceras
void inicializar_semilla();
double microsegundos();
double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n));
void mostrar_tiempo(int n, double t, int es_promedio,double subestimada,double ajustada, double sobreestimada);
double divisor(int seleccion, int n, float power);

#endif