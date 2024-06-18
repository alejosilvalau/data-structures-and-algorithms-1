#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *direction;
  int capacidad;
} ArregloEnteros;

ArregloEnteros *arreglo_enteros_crear(int capacidad) { return NULL; }

void arreglo_enteros_destruir(ArregloEnteros *arreglo) {
  for (int i = 0; i < arreglo->capacidad; i++) {
    free(arreglo->direction[i]);
  }
  free(arreglo->direction);
}

int arreglo_enteros_leer(ArregloEnteros *arreglo, int pos) {
  printf("%d", arreglo->direction[pos]);
}

void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato) {
  arreglo->direction[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros *arreglo) {
  return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo) {
  for (int i = 0; i < arreglo->capacidad; i++) {
    printf("%d", arreglo->direction[i]);
  }
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
  arreglo->direction = realloc(arreglo->direction, capacidad * sizeof(int));
}
