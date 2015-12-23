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

#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "utils.h"
#include "sumasubmax.h"


// Se establece la semilla para una serie de enteros pseudoaleatorios
void inicializar_semilla() {
   srand(time(NULL));
}

// Obtiene la hora del sistema en microsegundos
double microsegundos() {
   struct timeval t;
   if(gettimeofday(&t, NULL) < 0) return 0.0;
   return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Se generan números pseudoaleatorios entre -n y+n
void aleatorio(int v[], int n) {
   int i, m=2*n+1;
   for (i = 0; i < n; ++i) {
      v[i] = (rand()%m)-n;
   }
}

// Muestra el contenido de un vector
void mostrar_vector ( int v[], int n ) {
   int i;
   printf("[ ");
   for (i = 0; i < n; ++i) {
      printf("%2d ", v[i]);
   }
   printf("]");
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
double tiempo_promedio(int v[], int n,int (*suma)(int v[],int n)) {
   double t_inicial, t_final, t1_total;
   int i;

   // Se inicializa el vector
   aleatorio(v,n);

   t_inicial = microsegundos();
   // Se ejecuta el algoritmo K veces
   for (i = 0; i<K; ++i) { 
      suma(v, n);
   }
   t_final = microsegundos();
   // Se obtiene el tiempo de inicialización de vector y de ejecución del algoritmo
   t1_total = t_final-t_inicial;

   // Se obtiene el tiempo final dividiendo el tiempo de ejecucion por K
   return t1_total/K; 
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
void medir_tiempos(int (*suma)(int v[],int n),
     int selector[],float power[]){
   double t_inicio, t_fin, t_total;
   int n, i, promedio, v[64000];
   n = 500; promedio = 0;
   
   for (i = 0; i<8; ++i) {
      // Inicializamos el vector
      aleatorio(v,n);
      // Obtenemos los tiempos de ejecución
      t_inicio = microsegundos(); suma(v, n); t_fin = microsegundos();
      t_total = t_fin - t_inicio;
      // Si el valor es pequeño se hace un promedio
      if (t_total < 500) {
         promedio = 1;
         t_total = tiempo_promedio(v, n,suma);
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

void tiempos(){
   int selector[3]; float power[3];

   printf("Tiempos sumaSubMax1 \n\n");
   //Escoger cotas:
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada 
   selector[0]=NEXP;      selector[1]=NEXP;    selector[2]=NEXP;
   power[0]=1.8;          power[1]=2;            power[2]=2.2;  
   mostrar_cabecera(selector, power);
   //Escoger algoritmo a ser medido
   medir_tiempos(&sumaSubMax1, selector, power);

   printf("Tiempos sumaSubMax2\n\n");
   //Escoger cotas:
   //Cota subestimada  |  Cota ajustada        | Cota sobreestimada
   selector[0]=NEXP;      selector[1]=LINEAL;    selector[2]=NEXP;
   power[0]=0.8;          power[1]=0;            power[2]=1.2;
   mostrar_cabecera(selector, power);
   //Escoger algoritmo a ser medido
   medir_tiempos(&sumaSubMax2, selector, power);
}