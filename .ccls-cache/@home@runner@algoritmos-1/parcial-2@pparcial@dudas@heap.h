#include "tipos.h"

typedef struct _BHeap {
  void **arr;
  int capacidad;
  int ultimo;
  FuncionComparadora comp;
} * BHeap;

/**
 * Crea un heap vacio con una capacidad y una funcion de comparacion pasadas por
 * parametro.
 */
BHeap bheap_crear(int capacidad, FuncionComparadora comp);

/**
 * Destruye el heap pasado por parametro
 */
void bheap_destruir(BHeap heap, FuncionDestructora destr);

/**
 * retorna 1 si el heap esta vacio y 0 en caso contrario.
 */
int bheap_es_vacio(BHeap heap);

/**
 * Recorre los nodos utilizando busqueda por extension (BFS),
 * aplicando la funcion dada en cada elemento
 */
void bheap_recorrer(BHeap heap, FuncionVisitante visit);

/**
 * Agrega un elemento al heap, realocando el arreglo en caso de ser necesario
 */
BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy);

/**
* Elimina el elemento con mayor prioridad del heap, reacomodando los nodos
*/
void *bheap_eliminar(BHeap heap);
