struct nodo {
   int elem;
   int num_repeticiones;
   struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

arbol insertar(int e, arbol a);
arbol creararbol();        
int esarbolvacio(arbol);
posicion buscar(int, arbol);
arbol eliminararbol(arbol); 
posicion hijoizquierdo(arbol);
posicion hijoderecho(arbol);
int elemento(posicion);
int numerorepeticiones(posicion);
int altura(arbol);
void visualizar(arbol);
int testear ();
int tiempos();