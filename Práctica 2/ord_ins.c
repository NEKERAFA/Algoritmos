
// Algoritmo de ordenación por inserción
void ord_ins (int v[], int n) {
   int i, j, x;

   for (i = 2; i < n; i++) {
      x = v[i];
      j = i - 1;
      while ((j > 0) && (v[j] > x)) {
         v[j + 1] = v[j];
         j = j - 1;
      }
      v[j + 1] = x;
   }
}
