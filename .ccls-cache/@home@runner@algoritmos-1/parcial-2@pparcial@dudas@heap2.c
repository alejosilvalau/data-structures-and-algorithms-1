#include <assert.h>
#include <stdio.h>


void swap_int(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int padre(int i) {return (i - 1) / 2;}
int hijo_izq(int i) {return 2 * i +1;}
int hijo_der(int i) {return 2 * i + 2;}

void flotar(int* arr, int i, int n) {
  if (i == 0) return;
  int p = padre(i);
  if (arr[i] > arr[p]) {
    swap_int(&arr[i], &arr[p]);
    flotar(arr, p, n);
  }
}

void hundir(int* arr, int i, int n) {
  int j = i;
  if (hijo_izq(i) < n && arr[hijo_izq(i)] > arr[j]) j = hijo_izq(i);
  if (hijo_der(i) < n && arr[hijo_der(i)] > arr[j]) j = hijo_der(i);
  if (i != j) {
    swap_int(&arr[i], &arr[j]);
    hundir(arr, j, n);
  }
}

typedef struct _Heap {
int* data;
int cantidad, capacidad;
} * Heap;

void heap_insertar(Heap heap, int dato) {
  heap->cantidad++;
  heap->data[heap->cantidad - 1] = dato;
  //flotar(heap->data, heap->cantidad - 1, heap->cantidad);
}

void heap_eliminar(Heap heap) {
  heap->data[0] = heap->data[heap->cantidad - 1];
  heap->cantidad--;
  hundir(heap->data, 0, heap->cantidad);
}

// Cuando se inserta, se asume que entra en el array creado
// No hay una funcion para crear
