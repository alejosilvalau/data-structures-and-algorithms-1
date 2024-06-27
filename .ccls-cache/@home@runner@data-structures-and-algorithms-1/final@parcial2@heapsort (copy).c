#include <stdio.h>
#include <stdlib.h>

// gcc -Wall heapsort.c -g -o main
// valgrind ./main

// Intercambia los valores entre dos punetros a entero .
void swap_int(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// Devuelve la posicion del padre del elemento en la posicion i
int padre(int i) { return (i - 1) / 2; }

// Devuelve la posicion del hijo izquierdo del elemento en la posicion i
int izq(int i) { return i * 2 + 1; }

// Devuelve la posicion del hijo derecho del elemento en la posicion i
int der(int i) { return i * 2 + 2; }

// Hunde el elemento en la posicion pos del arreglo hasta que este cumpla la
// condicion de max - heap.n es la cantidad de elementos del arreglo void
void hundir(int pos, int *arr, int n) {
  int max_pos = pos;
  if (izq(pos) < n && arr[izq(pos)] > arr[max_pos])
    max_pos = izq(pos);
  if (der(pos) < n && arr[der(pos)] > arr[max_pos])
    max_pos = der(pos);
  if (max_pos != pos) {
    swap_int(&arr[pos], &arr[max_pos]);
    hundir(max_pos, arr, n);
  }
}
// Flota el elemento en la posicion pos hasta que el arreglo cumpla con la
// condicion de max - heap.n es la cantidad de elementos del arreglo.void
void flotar(int pos, int *arr, int n) {
  if (pos == 0)
    return;
  int pos_padre = padre(pos);
  if (arr[pos_padre] < arr[pos]) {
    swap_int(&arr[pos], &arr[pos_padre]);
    flotar(pos_padre, arr, n);
  }
}

// Función para convertir un arreglo en un max-heap
void construir_heap(int *arr, int n) {
  for (int i = padre(n - 1); i >= 0; i--) {
    hundir(i, arr, n);
  }
}

// Función de ordenamiento heapsort
void ordenar(int *arr, int n) {
  construir_heap(arr, n);
  for (int i = n - 1; i > 0; i--) {
    swap_int(&arr[0], &arr[i]); // Mueve el máximo al final
    hundir(0, arr, i); // Rehace el heap con los elementos restantes
  }
}

// Función principal para probar el ordenamiento
int main() {
  int arr[] = {3, 5, 1, 4, 2};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Arreglo original: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  ordenar(arr, n);

  printf("Arreglo ordenado: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
