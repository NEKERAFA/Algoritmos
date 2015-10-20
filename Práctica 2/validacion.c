/*
 * Práctica 2 - Algoritmos de Ordenación
 *
 * Autores
 *
 * -Rafael Alcalde Azpiazu
 * -Iván Anta Porto
 * -David Méndez Álvarez
 *
 * Fecha:
 *
 * Para esta práctica se van a implementar, validar y utilizar dos algoritmos 
 * de ordenación. Concretamente ordenación por inserción y ordenación shell.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

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
//Algoritmos implementados:
void ord_ins(int v[], int n);
void ord_shell(int v[], int n);

//Funciones para testear los algoritmos:
void test (void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n)
      ,int n);
void testear();

//Funciones para realizar la medición de tiempos
void medir_tiempos(void (*ordenar)(int v[],int n),void (*inicializar)(int v[],
      int n),int selector[],float power[]);
void mediciones();

//Funciones de inicialización de vectores
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);

//otras utilidades
void inicializar_semilla();
int esta_ordenado(int v[],int n);
void listar_vector( int v[], int n );
double microsegundos();
double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),
   void (*inicializar)(int v[],int n));
void mostrar_tiempo(int n, double t, int es_promedio,double subestimada
   ,double ajustada, double sobreestimada);
double divisor(int seleccion, int n, float power);

/*Implementación de las funciones:*/

//Función que inicializa la semilla de generación de números pseudo aleatorios
void inicializar_semilla() {
   srand(time(NULL));
}

//Se generan números pseudo aleatorios entre -n y +n
void aleatorio(int v [], int n) {
   int i, m=2*n+1;
   for (i=0; i < n; i++)
      v[i] = (rand() % m) - n;
}

//Se inicializa el vector ascendentemente
void ascendente(int v [], int n) {
   int i;
   for (i=0; i < n; i++)
      v[i] = i;
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

//Se inicializa el vector descendentemente
void descendente(int v [], int n){
   int i,j = (n-1);
   for (i=0; i < n; i++)
      v[i] = j--;
      
}

//Función que comprueba si un vector está ordenado
int esta_ordenado(int v[],int n){
   int i;

   for (i=0;i<(n-1);i++){ //Se recorre el vector
      if(v[i]>v[(i+1)]){ //Si el siguiente elemento es menor que el actual
         return 0; //El vector no está ordenado
      }
   }
   return 1;//Si no, el vector está ordenado
}
// Función que muestra todo el contenido de un vector
void listar_vector( int v[], int n ) {
	int i;

	printf("[ ");
	for (i = 0; i < n; ++i) {
		printf("%2d ", v[i]);
	}
	printf("]\n");
}

// Obtiene la hora del sistema en microsegundos
double microsegundos() {
   struct timeval t;
   if(gettimeofday(&t, NULL) < 0) return 0.0;
   return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Algoritmo de ordenación shell
void ord_shell( int v[], int n ) {
   int incremento = n;
   int i, tmp, j, seguir;

   do {
      incremento = incremento/2;
      for(i = incremento; i < n ; i++) {
         tmp = v[i]; j = i; seguir = 1;
         while (((j-incremento) >= 0) && seguir) {
            if(tmp < v[j-incremento]) {
               v[j] = v[j-incremento];
               j = j-incremento;
            } else { seguir = 0; }
         }
         v[j] = tmp;
      }
   } while (incremento > 1);
}

//Algoritmo de ordenación por inserción
void ord_ins (int v[], int n) {
   int i, j, x;

   for (i = 1; i < n; i++) {
      x = v[i];
      j = i - 1;
      while ((j > -1) && (v[j] > x)) {
         v[j + 1] = v[j];
         j--;
      }
      v[j + 1] = x;
   }
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

// Se testean los algoritmos en 3 casos de entrada: que el vector ya esté 
// ordenado, que esté ordenado inversamente y que esté desordenado
void testear(){
   int n = 10;   

   printf("\n+++Test de Ordenación por insercion con vector ordenado ascendentemente \n \n");
   test(&ord_ins,&ascendente,n);

   printf("\n+++Test de Ordenación por insercion con vector ordenado descendentemente \n \n");
   test(&ord_ins,&descendente,n);

   printf("\n+++Test de Ordenación por insercion con el vector desordenado \n \n");
   test(&ord_ins,&aleatorio,n);

   printf("\n+++Test de Ordenación de shell con vector ordenado ascendentemente \n \n");
   test(&ord_shell,&ascendente,n);

   printf("\n+++Test de Ordenación de shell con vector ordenado descendentemente \n \n");
   test(&ord_shell,&descendente,n);

   printf("\n+++Test de Ordenación de shell con el vector desordenado \n \n");
   test(&ord_shell,&aleatorio,n);
}

void medicion_insercion(){
   int selector[3];
   float power[3];

   printf("Ordenación por insercion con vector ordenado ascendentemente \n \n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=NEXP;    selector[1]=LINEAL;    selector[2]=NEXP;
   power[0]=0.8;         power[1]=0;            power[2]=1.2;

   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/(n^0.8)", "t(n)/n"
         ,"t(n)/n^1.2");
   medir_tiempos(&ord_ins,&ascendente,selector,power);

   printf("Ordenación por insercion con vector ordenado descendentemente \n\n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=NEXP;     selector[1]=NEXP;   selector[2]=NEXP;
   power[0]=1.8;          power[1]=2;           power[2]=2.2;

   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2"
      ,"t(n)/n^2.2");
   medir_tiempos(&ord_ins,&descendente,selector,power);

   printf("Ordenación por insercion con el vector desordenado \n \n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=NEXP;    selector[1]=NEXP;    selector[2]=NEXP;
   power[0]=1.8;         power[1]=2;          power[2]=2.2;

   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2",
      "t(n)/n^2.2");
   medir_tiempos(&ord_ins,&aleatorio,selector,power);

}

void medicion_shell(){
   int selector[3];
   float power[3];

   printf("Ordenación de shell con vector ordenado ascendentemente \n \n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=LINEAL;    selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=2;
   
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n", "t(n)/(n*log(n))"
      ,"t(n)/n^2");
   medir_tiempos(&ord_shell,&ascendente,selector,power);

   printf("Ordenación de shell con vector ordenado descendentemente \n \n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada
   selector[0]=LINEAL;    selector[1]=NLOGN;    selector[2]=NEXP;
   power[0]=0;         power[1]=0;           power[2]=2;
   
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n", "t(n)/(n*log(n))"
      ,"t(n)/n^2");
   medir_tiempos(&ord_shell,&descendente,selector,power);

   printf("Ordenación de shell con el vector desordenado \n \n");
   //Cota subestimada |   Cota ajustada     | Cota sobreestimada   
   selector[0]=LINEAL;     selector[1]=NEXP;   selector[2]=NEXP;
   power[0]=0;           power[1]=1.25;           power[2]=1.50;
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n", "t(n)/n^1.25",
      "t(n)/n^1.5");
   medir_tiempos(&ord_shell,&aleatorio,selector,power);

}

//Función que sirve para realizar la medición de los tiempos de los algoritmos en todos los casos
void mediciones(){
   medicion_insercion();
   medicion_shell();
}

// Función principal
void main(){
   int i;
   
   printf("\n\n\n");

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
      mediciones();
   }
}
