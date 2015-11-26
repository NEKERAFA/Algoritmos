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
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include "utils.h"

/** Implementación de las funciones *******************************************/

// Función que inicializa la semilla de generación de números pseudo aleatorios
void inicializar_semilla() {
   srand(time(NULL));
}

// Se generan números pseudo aleatorios entre -n y +n
void aleatorio(int v[], int n) {
   int i, m=2*n+1;
   for (i=0; i < n; i++)
      v[i] = (rand() % m) - n;
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
      case CONST  : result = 1; break;
      case LOGN   : result = log(n); break;
      case LINEAL : result = n; break;
      case NLOGN  : result = n*log(n); break;
      case NEXP   : result = pow (n,power); break;
      case N2LOGN : result = pow(n,2)*log(n); break;
   }
   return result;
}

// Función que imprime por pantalla la tabla de tiempos
void mostrar_tiempo(int n, double t, double subestimada, double ajustada,
   double sobreestimada) {
   printf("   %7d %15.3f %15.6f %15.6f %15.6f\n", n, t, t/subestimada, t/ajustada,
   t/sobreestimada);
}

void medir_tiempos(double tiempos[8][3]) {
/*    double t_inicio, t_fin, t1, t2;
   int n, i, j, k;
   int v[512000];
   n = 500; j = 1; i = 1;
   arbol a = creararbol();
   while((i<8)&&(n<=512000)) {
      // Inicializamos el vector
      aleatorio(v, n);
      // Obtenemos los tiempos de insercion
      t_inicio = microsegundos();
      for(k = 0; k<n; k++) a = insertar(v[k], a);
      t_fin = microsegundos();

      t1 = t_fin - t_inicio;
      // Si el tiempo es pequeño se continua al siguiente ciclo
      if (t1 < 500) {n*=2; a = eliminararbol(a); continue;}

      // Obtenemos los tiempos de busqueda
      t_inicio = microsegundos();
      for(k = 0; k<n; k++) buscar(v[k], a);
      t_fin = microsegundos();

      t2 = t_fin - t_inicio;
      // Si el tiempo es pequeño se continua al siguiente ciclo
      if (t2 < 500)  {n*=2; a = eliminararbol(a); continue;}

      // Se insertan los tiempos en la tabla
      printf("%10i %10i %10i\n", n, (int) t1, (int) t2);
      tiempos[j][0] = n; tiempos[j][1] = t1; tiempos[j][2] = t2;
      // Se actualizan las variables
      ++j; n*=2; a = eliminararbol(a); i++;
   }
   tiempos[0][0] = i;;
   //printf("%d",i);*/
}

// Muestra las mediciones de tiempos de insercion en el arbol
void medicion_insercion( double v[12][3] ) {
/*   int selector[3];
   float power[3];
   int i;

   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=LINEAL;    selector[1]=NEXP;    selector[2]=NEXP;
   power[0]=0;            power[1]=1.25;        power[2]=1.5;

   printf("\n\n Tiempos en la inserción en el arbol\n\n");
   printf("%10s %15s %15s %15s %15s\n", "", "", "Cota subestimada",
          "Cota ajustada", "Cota sobrestimada");
   printf("%10s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n", "t(n)/n^1.25",
      "t(n)/n^1.5");
   for(i = 1; i<v[0][0]; i++) {
      mostrar_tiempo((int) v[i][0], v[i][1],
         divisor(selector[0], (int) v[i][0], power[0]),
         divisor(selector[1], (int) v[i][0], power[1]),
         divisor(selector[2], (int) v[i][0], power[2]));
   }*/
}

void medicion_busqueda( double v[12][3] ) {
/*   int selector[3];
   float power[3];
   int i;

   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=LINEAL;    selector[1]=NEXP;    selector[2]=NEXP;
   power[0]=0;            power[1]=1.25;        power[2]=1.5;

   printf("\n\n Tiempos en la búsqueda en el arbol\n\n");
   printf("%10s %15s %15s %15s %15s\n", "", "", "Cota subestimada",
          "Cota ajustada", "Cota sobrestimada");
   printf("%10s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n", "t(n)/n^1.25",
      "t(n)/n^1.5");
   for(i = 1; i<v[0][0]; i++) {
      mostrar_tiempo((int) v[i][0], v[i][2],
         divisor(selector[0], (int) v[i][0], power[0]),
         divisor(selector[1], (int) v[i][0], power[1]),
         divisor(selector[2], (int) v[i][0], power[2]));
   }*/
}
