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

// Definición de cabeceras
// Algoritmos
int sumaSubMax1( int v[], int n );
int sumaSubMax2( int v[], int n );
// Tests
void test1();
void test2();
// Medición de tiempos
void medicion_tiempos1();
void medicion_tiempos2();
// Utilidades
double tiempo_promedio_alg1( int v[], int n );
double tiempo_promedio_alg2( int v[], int n );
void listar_vector( int v[], int n );
void mostrar_tiempo_cuadratico( int n, double t, int es_promedio );
void mostrar_tiempo_lineal( int n, double t, int es_promedio );
void inicializar_semilla();
void aleatorio( int v[], int n );
double microsegundos();

// Algoritmo 1
int sumaSubMax1( int v[], int n ) {
	int i, j, sumaMax = 0;
	for (i = 0; i < n; ++i) {
		int estaSuma = 0;
		for (j = i; j < n; ++j) {
			estaSuma = estaSuma + v[j];
			if (estaSuma > sumaMax) {
				sumaMax = estaSuma;
			}
		} // Fin segundo para
	} // Fin primer para
	return sumaMax;
}

// Algoritmo 2
int sumaSubMax2( int v[], int n ) {
	int estaSuma, sumaMax, j;
	estaSuma = 0;
	sumaMax = 0;
	for (j = 0; j < n; ++j) {
		estaSuma = estaSuma + v[j];
		if (estaSuma > sumaMax) {
			sumaMax = estaSuma;
		} else if (estaSuma < 0) {
			estaSuma = 0;
		}
	}
	return sumaMax;
}

// Test 1 con vectores definidos
void test1() {
	int v[][5] = { {-9,  2, -5, -4,  6},
	               { 4,  0,  9,  2,  5},
	               {-2, -1, -9, -7, -1},
	               { 9, -2,  1, -7, -8},
	               {15, -2, -5, -4, 16},
	               { 7, -5,  6,  7, -7} };
	int i;
	printf("Test 1\n");
	printf("%19s sumaSubMax1 sumaSubMax2\n", "");
	for(i = 0; i < 6; ++i) {
		listar_vector(v[i], 5);
		printf("%8d\t%8d\n", sumaSubMax1(v[i], 5), sumaSubMax2(v[i], 5));
	}
}

// Test 2 con vectores generados pseudoaleatoriamente
void test2() {
	const int tam = 9;
	const int nvect = 5;
	int v[nvect][tam];
	int i;
	for(i = 0; i < nvect; ++i) { aleatorio(v[i], tam); }
	printf("Test 2\n");
	printf("%30s sumaSubMax1 sumaSubMax2\n", "");
	for(i = 0; i < nvect; ++i) {
		listar_vector(v[i], tam);
		printf("%8d\t%8d\n", sumaSubMax1(v[i], tam), sumaSubMax2(v[i], tam));
	}
}

// Medición del tiempo aplicando vectores aleatorios de n tamaño y obteniendo
// los tiempos de ejecución en el primer algoritmo
void medicion_tiempos1() {
 	double t_inicio, t_fin, t_total;
	int n = 500;
	int i;
	int promedio = 0;
	int v[32000];

	// Vamos a determinar los tiempos de los vectores aleatorios de tamaño n unas
	// 7 veces
	printf("\nsumaSubMax 1\n");
	printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2",
	"t(n)/n^2.2");
	for (i = 0; i<7; ++i) {
		// Inicializamos el vector
		aleatorio(v, n);
		// Obtenemos los tiempos de ejecución
		t_inicio = microsegundos();
		sumaSubMax1(v, n);
		t_fin = microsegundos();
		t_total = t_fin - t_inicio;
		// Si el valor es pequeño se hace un promedio
		if (t_total < 500) {
			promedio = 1;
			t_total = tiempo_promedio_alg1(v, n);
		}
		mostrar_tiempo_cuadratico(n, t_total, promedio);
		promedio = 0;
		n = n*2;
	}
	printf("*: Tiempo promedio de 1000 ejecuciones del algoritmo\n\n");
}

// Medición del tiempo aplicando vectores aleatorios de n tamaño y obteniendo
// los tiempos de ejecución en el segundo algoritmo
void medicion_tiempos2() {
 	double t_inicio, t_fin, t_total;
	int n = 500;
	int i;
	int promedio = 0;
	int v[2048000];

	// Vamos a determinar los tiempos de los vectores aleatorios de tamaño n unas
	// 7 veces
	printf("\nsumaSubMax 2\n");
	printf("%15s %15s %15s %15s %15s\n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n",
	"t(n)/n^1.2");
	for (i = 0; i<13; ++i) {
		// Inicializamos el vector
		aleatorio(v, n);
		// Obtenemos los tiempos de ejecución
		t_inicio = microsegundos();
		sumaSubMax2(v, n);
		t_fin = microsegundos();
		t_total = t_fin - t_inicio;
		// Si el valor es pequeño se hace un promedio
		if (t_total < 500) {
			promedio = 1;
			t_total = tiempo_promedio_alg2(v, n);
		}
		mostrar_tiempo_lineal(n, t_total, promedio);
		promedio = 0;
		n = n*2;
	}
	printf("*: Tiempo promedio de 1000 ejecuciones del algoritmo\n\n");
}

// Lista los vectores
void listar_vector( int v[], int n ) {
	int i;
	printf("[ ");
	for (i = 0; i < n; ++i) {
		printf("%2d ", v[i]);
	}
	printf("]");
}

// Muestra una linea con los tiempos en base a un algoritmo de orden cuadrático
void mostrar_tiempo_cuadratico(int n, double t, int es_promedio) {
	if (es_promedio) {
		printf("(*)%12d %15.3f %15.6f %15.6f %15.6f\n", n, t,
		t/pow((double) n, 1.8), t/pow((double) n, 2.0), t/pow((double) n, 2.2));
	} else {
		printf("%15d %15.3f %15.6f %15.6f %15.6f\n", n, t,
		t/pow((double) n, 1.8), t/pow((double) n, 2.0), t/pow((double) n, 2.2));
	}
}

// Muestra una linea con los tiempos en base a un algoritmo de orden lineal
void mostrar_tiempo_lineal(int n, double t, int es_promedio) {
	if (es_promedio) {
		printf("(*)%12d %15.3f %15.6f %15.6f %15.6f\n", n, t,
		t/pow((double) n, 0.8), t/n, t/pow((double) n, 1.2));
	} else {
		printf("%15d %15.3f %15.6f %15.6f %15.6f\n", n, t,
		t/pow((double) n, 0.8), t/n, t/pow((double) n, 1.2));
	}
}

// Hace una media de tiempos para el primer algoritmo (Usado para tiempos pequeños)
double tiempo_promedio_alg1(int v[], int n) {
	double t_inicial, t_final, t1_total, t2_total;
	int i;

	t_inicial = microsegundos();
	for (i = 0; i<1000; ++i) {
		aleatorio(v, n);
		sumaSubMax1(v, n);
	}
	t_final = microsegundos();
	t1_total = t_final-t_inicial;
	t_inicial = microsegundos();
	for (i = 0; i<1000; ++i) {
		aleatorio(v, n);
	}
	t_final = microsegundos();
	t2_total = t_final-t_inicial;
	return (t1_total-t2_total)/1000;
}

// Hace una media de tiempos para el segundo algoritmo (Usado para tiempos pequeños)
double tiempo_promedio_alg2(int v[], int n) {
	double t_inicial, t_final, t1_total, t2_total;
	int i;

	t_inicial = microsegundos();
	for (i = 0; i<1000; ++i) {
		aleatorio(v, n);
		sumaSubMax2(v, n);
	}
	t_final = microsegundos();
	t1_total = t_final-t_inicial;
	t_inicial = microsegundos();
	for (i = 0; i<1000; ++i) {
		aleatorio(v, n);
	}
	t_final = microsegundos();
	t2_total = t_final-t_inicial;
	t_final = microsegundos();
	t1_total = t_final-t_inicial;
	t_inicial = microsegundos();
	for (i = 0; i<1000; ++i) {
		aleatorio(v, n);
	}
	t_final = microsegundos();
	t2_total = t_final-t_inicial;
	return (t1_total-t2_total)/1000;
}

// Se establece la semilla para una serie de enteros pseudoaleatorios
void inicializar_semilla() {
	srand(time(NULL));
}

// Se generan números pseudoaleatorios entre -n y+n
void aleatorio(int v[], int n) {
	int i, m=2*n+1;
	for (i = 0; i < n; ++i) {
		v[i] = (rand()%m)-n;
	}
}

// Obtiene la hora del sistema en microsegundos
double microsegundos() {
	struct timeval t;
	if(gettimeofday(&t, NULL) < 0) return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

/** Función principal *********************************************************/
int main(int argv, char argc[]) {
	int i;
	inicializar_semilla();
	// test1();
	// test2();
	for(i = 0; i < 3; ++i) { medicion_tiempos1(); }
	for(i = 0; i < 3; ++i) { medicion_tiempos2(); }
	return 0;
}
