#include "heap.h"
#include <assert.h>
#include <stdlib.h>

static void swap_void(void **x, void **y) {
  void *temp = *x;
  *x = *y;
  *y = temp;
}

static int ind_padre(int i) { return (i - 1) / 2; }
static int ind_hijo_izq(int i) { return 2 * i + 1; }
static int ind_hijo_der(int i) { return 2 * i + 2; }

static void flotar(void **arr, int indUltimo, FuncionComparadora comp) {
  if (indUltimo == 0)
    return;
  int indPadre = ind_padre(indUltimo);
  if (comp(arr[indUltimo], arr[indPadre]) > 0) {
    swap_void(&arr[indUltimo], &arr[indPadre]);
    flotar(arr, indPadre, comp);
  }
}

static void hundir(void **arr, int indIni, int indUlt, FuncionComparadora comp) {
  int j = indIni;
  if (ind_hijo_izq(indIni) < (indUlt+1) && comp(arr[ind_hijo_izq(indIni)], arr[j]) > 0)
    j = ind_hijo_izq(indIni);
  if (ind_hijo_der(indIni) < (indUlt+1) && comp(arr[ind_hijo_der(indIni)], arr[j]) > 0)
    j = ind_hijo_der(indIni);
  if (indIni != j) {
    swap_void(&arr[indIni], &arr[j]);
    hundir(arr, j, indUlt, comp);
  }
}

BHeap bheap_crear(int capacidad, FuncionComparadora comp) {
  BHeap heap = malloc(sizeof(struct _BHeap));
  assert(heap != NULL);
  heap->arr = malloc(sizeof(void *) * (capacidad ));
  assert(heap->arr != NULL);

  heap->capacidad = capacidad;
  heap->ultimo = -1;
  heap->comp = comp;

  return heap;
}

void bheap_destruir(BHeap heap, FuncionDestructora destr) {
  destr(heap->arr);
  free(heap);
}

int bheap_es_vacio(BHeap heap) { return heap->ultimo == -1; }

void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
  if (!bheap_es_vacio(heap)) {
    for (int i = 0; i <= heap->ultimo; i++) {
      visit(heap->arr[i]);
    }
  }
}

BHeap bheap_insertar(BHeap heap, void *dato, FuncionCopiadora copy) {
  if (heap->ultimo == heap->capacidad - 1) {
    heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad * 2);
    heap->capacidad *= 2;
  }
  heap->ultimo++;
  heap->arr[heap->ultimo] = copy(dato);

  flotar(heap->arr, heap->ultimo, heap->comp);
  
  return heap;
}

void *bheap_eliminar(BHeap heap) {
  void *retDato = heap->arr[0];
  heap->arr[0] = heap->arr[heap->ultimo];
  heap->ultimo--;
  hundir(heap->arr, 0, heap->ultimo, heap->comp);
  return retDato;
}



// BHeap bheap_eliminar(BHeap heap, void *dato, FuncionDestructora destr,
//                      FuncionComparadora comp) {
//   if (!bheap_es_vacio(heap)) {
//     int i;
//     for (i = 1; i <= heap->ultimo; i++) {
//       if (comp(heap->arr[i], dato) == 0) {
//         heap->arr[i] = heap->arr[heap->ultimo];
//         destr(heap->arr[i]);
//         heap->ultimo--;
//       }
//     }
//     while (comp(heap->arr[i], heap->arr[i * 2]) < 0 ||
//            comp(heap->arr[i], heap->arr[i * 2 + 1]) < 0) {
//       void *aux;

//       if (comp(heap->arr[i * 2], heap->arr[i * 2 + 1]) > 0) {
//         aux = heap->arr[i * 2];
//         heap->arr[i * 2] = heap->arr[i];
//       } else {
//         aux = heap->arr[i * 2 + 1];
//         heap->arr[i * 2 + 1] = heap->arr[i];
//       }

//       heap->arr[i] = aux;
//     }
//   }
//   return heap;
// }
