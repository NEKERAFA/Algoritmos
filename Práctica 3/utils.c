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
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "utils.h"

/*Implementación de las funciones:*/

//Función que inicializa la semilla de generación de números pseudo aleatorios
void inicializar_semilla() {
   srand(time(NULL));
}


//Función que calcula el divisor en el cálculo de tiempos
double divisor(int seleccion, int n, float power){

   switch(seleccion){
      case CONST : 
         return 1;
      case LOGN : 
         return log(n);
      case LINEAL :
         return n;
      case NLOGN :
         return n * log (n);
      case NEXP :
         return pow (n,power);
      case N2LOGN :
         return pow(n,2)*log(n);
   }
}



// Obtiene la hora del sistema en microsegundos
double microsegundos() {
   struct timeval t;
   if(gettimeofday(&t, NULL) < 0) return 0.0;
   return (t.tv_usec + t.tv_sec * 1000000.0);
}


// Función que calcula el tiempo de un algoritmo mediante el promedio de K 
// ejecuciones
double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),
       void (*inicializar)(int v[],int n)) {
   double t_inicial, t_final, t1_total, t2_total;
   int i;

   t_inicial = microsegundos();
//Se inicializa el vector y se ejecuta el algoritmo K veces
   for (i = 0; i< K; ++i) { 
      inicializar(v, n);
      ordenar(v, n);
   }

   t_final = microsegundos();
//Se obtiene el tiempo de inicialización de vector y de ejecución del algoritmo
   t1_total = t_final-t_inicial;

   t_inicial = microsegundos();
// se inicializa K veces el vector   
   for (i = 0; i< K; ++i) { 
      inicializar(v, n);
   }
   t_final = microsegundos();
//se obtiene el tiempo de inicialización del vector
   t2_total = t_final-t_inicial; 
//Se obtiene el tiempo restando al tiempo de inicialización y ejecución el 
//tiempo de inicialización, y dividiendo este resultado por K
   return (t1_total-t2_total)/K; 
}

// Función que imprime por pantalla la tabla de tiempos
void mostrar_tiempo(int n, double t, int es_promedio,double subestimada,
      double ajustada, double sobreestimada) {

   if (es_promedio) {//Si es promedio se muestra un asterisco
      printf("(*)");
   } else {// Si no es promedio no se muestra
      printf("   ");
   }
   //Se imprime la línea de tiempos correspondiente
   printf("%12d %15.3f %15.6f %15.6f %15.6f\n", n, t, t/ subestimada, t/ ajustada, t/ sobreestimada);
}

//Función que se encarga de medir los tiempos
void medir_tiempos(void (*ordenar)(int v[],int n),
      void (*inicializar)(int v[],int n),int selector[],float power[]){
   double t_inicio, t_fin, t_total;
   int n = 500;
   int i;
   int promedio = 0;
   int v[32000];

   
   for (i = 0; i<7; ++i) {
      // Inicializamos el vector
      inicializar(v, n);
      // Obtenemos los tiempos de ejecución
      t_inicio = microsegundos();
      ordenar(v, n);
      t_fin = microsegundos();
      t_total = t_fin - t_inicio;
      // Si el valor es pequeño se hace un promedio
      if (t_total < 500) {
         promedio = 1;
         t_total = tiempo_promedio(v, n,ordenar,inicializar);
      }
      //Se muestran los tiempos
      mostrar_tiempo(n, t_total, promedio,divisor(selector[0],n,power[0]),
            divisor(selector[1],n,power[1]),divisor(selector[2],n,power[2]));
      //Se resetea la variable de promedios
      promedio = 0;
      // Se duplica el tamaño del vector
      n = n*2;
   }
   printf("*: Tiempo promedio de %d ejecuciones del algoritmo\n\n",K);
}

// Función para testear los algoritmos
void test (void (*ordenar)(int v[],int n),void (*inicializar)
      (int v[],int n),int n){
   int v[n];
   
   printf("·Se inicializa el vector\n");
   inicializar(v,n);

   listar_vector(v,n);

   printf("·Se procede a ordenar el vector: \n");
   ordenar(v,n);
   
   listar_vector(v,n);

   if(esta_ordenado(v,n)){
      printf("\nTEST SUPERADO \n");   
   } else {
      printf("\n************TEST FALLADO************\n");   
   }
}