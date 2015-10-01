#include <stdio.h>

void ord_shell( int v[], int n ) {
   int incremento = n;
   int i, tmp, j, seguir;

   do {
      incremento = incremento/2;
      for(i = incremento+1; i < n ; i++) {
         tmp = v[i]; j = i; seguir = 1;
         while (((j-incremento) > 0) && seguir) {
            if(tmp < v[j-incremento]) {
               v[j] = v[j-incremento];
               j = j-incremento;
            } else { seguir = 0; }
         }
         v[j] = tmp;
      }
   } while (incremento > 1);
}
