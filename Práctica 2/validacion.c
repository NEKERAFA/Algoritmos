#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

//Definición de cabeceras
//Algoritmos implementados:
void ord_ins(int v[], int n);
void ord_shell(int v[], int n);

//Funciones para testear los algoritmos:
void test (void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),int n);
void testear();

//Funciones para realizar la medición de tiempos
void medir_tiempos(void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),float subestimada,float ajustada, float sobreestimada);
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
double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n));
void mostrar_tiempo(int n, double t, int es_promedio,float subestimada,float ajustada, float sobreestimada);

//Implementación de las funciones:
void inicializar_semilla() {
   srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudo aleatorio entre -n y +n */
   int i, m=2*n+1;
   for (i=0; i < n; i++)
      v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
   int i;
   for (i=0; i < n; i++)
      v[i] = i;
}

void descendente(int v [], int n){
   int i,j = (n-1);
   for (i=0; i < n; i++)
      v[i] = j--;
      
}

int esta_ordenado(int v[],int n){
   int i;
   for (i=0;i<(n-1);i++){
      if(v[i]>v[(i+1)]){
         return 0;
      }
   }
   return 1;
}
// Lista los vectores
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

void ord_shell( int v[], int n ) {
   int incremento = n;
   int i, tmp, j, seguir;

   do {
      incremento = incremento/2;
      for(i = incremento; i < n ; i++) {
         tmp = v[i]; j = i; seguir = 1;
         while (((j-incremento) > -1) && seguir) {
            if(tmp < v[j-incremento]) {
               v[j] = v[j-incremento];
               j = j-incremento;
            } else { seguir = 0; }
         }
         v[j] = tmp;
      }
   } while (incremento > 1);
}

double tiempo_promedio(int v[], int n,void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n)) {
   double t_inicial, t_final, t1_total, t2_total;
   int i;

   t_inicial = microsegundos();
   for (i = 0; i<1000; ++i) {
      inicializar(v, n);
      ordenar(v, n);
   }
   t_final = microsegundos();
   t1_total = t_final-t_inicial;
   t_inicial = microsegundos();
   for (i = 0; i<1000; ++i) {
      inicializar(v, n);
   }
   t_final = microsegundos();
   t2_total = t_final-t_inicial;
   return (t1_total-t2_total)/1000;
}

void mostrar_tiempo(int n, double t, int es_promedio,float subestimada,float ajustada, float sobreestimada) {
   if (es_promedio) {
      printf("(*)%12d %15.3f %15.6f %15.6f %15.6f\n", n, t, t/pow((double) n, subestimada), t/pow((double) n, ajustada), t/pow((double) n, sobreestimada));
   } else {
      printf("%15d %15.3f %15.6f %15.6f %15.6f\n", n, t, t/pow((double) n, subestimada), t/pow((double) n, ajustada), t/pow((double) n, sobreestimada));
   }
}


void medir_tiempos(void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),float subestimada,float ajustada, float sobreestimada){
   double t_inicio, t_fin, t_total;
   int n = 500;
   int i;
   int promedio = 0;
   int v[32000];

   // Vamos a determinar los tiempos de los vectores aleatorios de tamaño n unas
   // 7 veces
   
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
      mostrar_tiempo(n, t_total, promedio,subestimada,ajustada,sobreestimada);
      promedio = 0;
      n = n*2;
   }
   printf("*: Tiempo promedio de 1000 ejecuciones del algoritmo\n\n");
}


void test (void (*ordenar)(int v[],int n),void (*inicializar)(int v[],int n),int n){
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

/*Los algoritmos deben superar 3 casos de entrada distinta, que esté ordenada ascendentemente, descendentemente y que este desordenada */

void testear(){
   int n = 10;   
/*
   printf("\n+++Test de Ordenación por insercion con vector ordenado ascendentemente \n \n");
   test(&ord_ins,&ascendente,n);

   printf("\n+++Test de Ordenación por insercion con vector ordenado descendentemente \n \n");
   test(&ord_ins,&descendente,n);

   printf("\n+++Test de Ordenación por insercion con el vector desordenado \n \n");
   test(&ord_ins,&aleatorio,n);
*/
   printf("\n+++Test de Ordenación de shell con vector ordenado ascendentemente \n \n");
   test(&ord_shell,&ascendente,n);

   printf("\n+++Test de Ordenación de shell con vector ordenado descendentemente \n \n");
   test(&ord_shell,&descendente,n);

   printf("\n+++Test de Ordenación de shell con el vector desordenado \n \n");
   test(&ord_shell,&aleatorio,n);
}

void mediciones(){
/*
   printf("Ordenación por insercion con vector ordenado ascendentemente \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2","t(n)/n^2.2");
   medir_tiempos(&ord_ins,&ascendente,1.8,2.0,2.2);

   printf("Ordenación por insercion con vector ordenado descendentemente \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2","t(n)/n^2.2");
   medir_tiempos(&ord_ins,&descendente,1.8,2.0,2.2);

   printf("Ordenación por insercion con el vector desordenado \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2","t(n)/n^2.2");
   medir_tiempos(&ord_ins,&aleatorio,1.8,2.0,2.2);
*/
   printf("Ordenación de shell con vector ordenado ascendentemente \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.0", "t(n)/n^1.25","t(n)/n^1.5");
   medir_tiempos(&ord_shell,&ascendente,1.0,1.25,1.5);

   printf("Ordenación de shell con vector ordenado descendentemente \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.0", "t(n)/n^1.25","t(n)/n^1.5");
   medir_tiempos(&ord_shell,&descendente,1.0,1.25,1.5);

   printf("Ordenación de shell con el vector desordenado \n \n");
   printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.0", "t(n)/n^1.25","t(n)/n^1.5");
   medir_tiempos(&ord_shell,&aleatorio,1.0,1.25,1.5);
}

void main(){
   int i;
   
   printf("\n\n\n");
   //Se inicializa la semilla para permitir la generación pseudoaleatoria de valores
   inicializar_semilla();

   printf("TEST DE LOS ALGORITMOS\n\n\n");

   testear();

   printf("\n\n\n");
   printf("MEDICION DE TIEMPOS\n\n\n");
   for(i = 0;i<4;i++){
      mediciones();
   }
}
