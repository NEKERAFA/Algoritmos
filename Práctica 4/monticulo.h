#ifndef __MONTICULOS_ALG__
#define __MONTICULOS_ALG__

#define TAM 128000
typedef struct {
   int vector[TAM];
   int ultimo;
} monticulo;

void inicializar_monticulo(monticulo * m);
void crear_monticulo(int [], int, monticulo *);
void insertar(monticulo * m, int e);
int eliminar_menor(monticulo *);
void ord_monticulo(int v[], int n);
void testear();

#endif