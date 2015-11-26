#include <stdio.h>
#include <stdlib.h>
#include "monticulo.h"

void hundir(monticulo * m, int i) {
   int hi, hd;
   int j;

   do {
      hi = 2 * i + 1;
      hd = 2 * i + 2;
      j = i;

      if ((hd <= m->ultimo) && (m->vector[hd] < m->vector[i]))
         i = hd;

      if ((hi <= m->ultimo) && (m->vector[hi] < m->vector[i]))
         i = hi;

      int temp = m->vector[i];
      m->vector[i] = m->vector[j];
      m->vector[j] = temp;
      //swap(m, i, j);

   } while (j != i);
}

int eliminar_menor(monticulo * m) {
   int x;

   if (m->ultimo == -1) {
      printf("Empty heap");
      exit(1);
   }
   else {
      x = m->vector[0];
      m->vector[0] = m->vector[m->ultimo];
      m->ultimo = m->ultimo - 1;

      if (m->ultimo > -1) {
         hundir(m, 0);
      }

      return x;
   }
}

void crear_monticulo(int v[], int n, monticulo * m) {
   int i;
   
   for (i = 0; i < n; i++) {
      m->vector[i] = v[i];
   }
   
   m->ultimo = n - 1;
   
   for (i = (n+1)/2-1; i >= 0; i--) {
      hundir(m, i);
   }
}

void inicializar_monticulo(monticulo * m) {
   m->ultimo = -1;
}

void ord_monticulo(int v[], int n) {
   monticulo m;
   int i;
   
   inicializar_monticulo(&m);
   crear_monticulo(v, n, &m);
   for (i = 0; i < n; i++) {
      v[i] = eliminar_menor(&m);
   }
}

