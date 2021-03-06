/*
 * Práctica 4 - Montículos
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha: 09/12/2015
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include "monticulo.h"
#include "utils.h"

/** Implementación de las funciones *******************************************/

// Función que inicializa la semilla de generación de números pseudo aleatorios
void inicializar_semilla() {
   srand(time(NULL));
}

// Se generan números pseudo aleatorios entre -n y +n
void aleatorio(int v[], int n) {
   int i, m=2*n+1;
   for (i=0; i < n; i++) v[i] = (rand() % m) - n;
}

//Se inicializa el vector ascendentemente
void ascendente(int v [], int n) {
   int i;
   for (i=0; i < n; i++) v[i] = i;
}

//Se inicializa el vector descendentemente
void descendente(int v [], int n){
   int i,j = (n-1);
   for (i=0; i < n; i++) v[i] = j--;
}

// Obtiene la hora del sistema en microsegundos
double microsegundos() {
   struct timeval t;
   if(gettimeofday(&t, NULL) < 0) return 0.0;
   return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Función que calcula el divisor en el cálculo de tiempos
double divisor(int seleccion, int n, float power){
   double result;
   switch(seleccion){
      case CONST  : result = 1;               break;
      case LOGN   : result = log(n);          break;
      case LINEAL : result = n;               break;
      case NLOGN  : result = n*log(n);        break;
      case NEXP   : result = pow (n,power);   break;
      case N2LOGN : result = pow(n,2)*log(n); break;
   }
   return result;
}

// Función que muestra el string de la función
void division(int seleccion, float power) {
   switch(seleccion){
      case CONST  : printf("%15s ", "t(n)");                break;
      case LOGN   : printf("%15s ", "t(n)/log(n)");         break;
      case LINEAL : printf("%15s ", "t(n)/n");              break;
      case NLOGN  : printf("%15s ", "t(n)/n*log(n)");       break;
      case NEXP   : printf("%11s%3.2f ", "t(n)/n^", power); break;
      case N2LOGN : printf("%15s ", "t(n)/n^2*log(n)");     break;
   }
   
}

// Función que calcula el tiempo de un algoritmo mediante el promedio de K 
// ejecuciones
double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),
       void (*inicializar)(int v[],int n)) {
   double t_inicial, t_final, t1_total, t2_total;
   int i;

   t_inicial = microsegundos();
   // Se inicializa el vector y se ejecuta el algoritmo K veces
   for (i = 0; i<K; ++i) { 
      inicializar(v, n);
      ordenar(v, n);
   }
   t_final = microsegundos();
   // Se obtiene el tiempo de inicialización de vector y de ejecución del algoritmo
   t1_total = t_final-t_inicial;

   t_inicial = microsegundos();
   // Se inicializa K veces el vector   
   for (i = 0; i<K; ++i) inicializar(v, n);
   t_final = microsegundos();
   // Se obtiene el tiempo de inicialización del vector
   t2_total = t_final-t_inicial; 
   // Se obtiene el tiempo restando al tiempo de inicialización y ejecución el 
   // tiempo de inicialización, y dividiendo este resultado por K
   return (t1_total-t2_total)/K; 
}

// Función que imprime por pantalla la tabla de tiempos
void mostrar_tiempo(int n, double t, int es_promedio, double subestimada,
                    double ajustada, double sobreestimada) {
   if (es_promedio) printf("(*)");
   else printf("   ");
   printf("%12d %15.3f %15.6f %15.6f %15.6f\n", n, t, t/subestimada,
          t/ajustada, t/sobreestimada);
}

//Función que se encarga de medir los tiempos
void medir_tiempos(void (*ordenar)(int v[],int n),
     void (*inicializar)(int v[],int n),int selector[],float power[]){
   double t_inicio, t_fin, t_total;
   int n, i, promedio, v[64000];
   n = 500; promedio = 0;
   
   for (i = 0; i<8; ++i) {
      // Inicializamos el vector
      inicializar(v, n);
      // Obtenemos los tiempos de ejecución
      t_inicio = microsegundos(); ordenar(v, n); t_fin = microsegundos();
      t_total = t_fin - t_inicio;
      // Si el valor es pequeño se hace un promedio
      if (t_total < 500) {
         promedio = 1;
         t_total = tiempo_promedio(v, n,ordenar, inicializar);
      }
      // Se muestran los tiempos
      mostrar_tiempo(n, t_total, promedio, divisor(selector[0], n, power[0]),
            divisor(selector[1], n, power[1]), divisor(selector[2], n, power[2]));
      // Se resetea la variable de promedios
      promedio = 0;
      // Se duplica el tamaño del vector
      n = n*2;
   }
   printf("*: Tiempo promedio de %d ejecuciones del algoritmo\n\n",K);
}

// Muestra la cabecera al ordenar
void mostrar_cabecera(int selector[], float power[]) {
   printf("%31s%15s %15s %15s\n", "", "Cota subestimada", "Cota ajustada",
          "Cota sobrestimada");
   printf("%15s %15s ", "n", "t(n)");
   division(selector[0], power[0]);
   division(selector[1], power[1]);
   division(selector[2], power[2]);
   printf("\n");
}

// Inserta elementos en un monticulo
void insertar_vmonticulo(int v[], int n) {
   monticulo m; int i;
   inicializar_monticulo(&m);
   for (i = 0; i < n; i++) insertar(&m, v[i]);
}

void crear_vmonticulo(int v[], int n) {
   monticulo m;
   crear_monticulo(v, n, &m);
}

// Mide los tiempos de insertar en un monticulo
void medicion_inicializacion_monticulos() {
   int selector[3]; float power[3];

   printf("Insertar n elementos en un monticulo \n\n");
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
 /*  selector[0]=LINEAL;      selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=1.4;
 */
   selector[0]=NEXP;      selector[1]=LINEAL;    selector[2]=NEXP;
   power[0]=0.8;          power[1]=0;            power[2]=1.2;  
   mostrar_cabecera(selector, power);
   medir_tiempos(&insertar_vmonticulo, &aleatorio, selector, power);

   printf("Crear monticulo de n elementos\n\n");
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
   selector[0]=NEXP;      selector[1]=LINEAL;    selector[2]=NEXP;
   power[0]=0.8;          power[1]=0;            power[2]=1.2;
   mostrar_cabecera(selector, power);
   medir_tiempos(&crear_vmonticulo, &aleatorio, selector, power);
}


// Mide los tiempos de monticulo
void medicion_ord_monticulos(){
   int selector[3]; float power[3];

   printf("Ordenación por montículo con vector ordenado ascendentemente \n\n");
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
   selector[0]=LINEAL;      selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=1.4;
   mostrar_cabecera(selector, power);
   medir_tiempos(&ord_monticulo, &ascendente, selector, power);

   printf("Ordenación por montículo con vector ordenado descendentemente \n\n");
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
   selector[0]=LINEAL;      selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=1.4;
   mostrar_cabecera(selector, power);
   medir_tiempos(&ord_monticulo, &descendente, selector, power);

   printf("Ordenación por montículo con el vector desordenado \n\n");
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
   selector[0]=LINEAL;      selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=1.4;
   mostrar_cabecera(selector, power);
   medir_tiempos(&ord_monticulo, &aleatorio, selector, power);
}

void tiempos() {
   int i;
   printf("==== CREACIÓN DE MONTICULOS ====\n");
   for (i = 0; i < 3; i++) medicion_inicializacion_monticulos();
   printf("==== ORDENAMIENTO POR MONTICULOS ====\n");
   for (i = 0; i < 3; i++) medicion_ord_monticulos();
}
