#include "arregloenteros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArregloEnteros *arreglo_enteros_crear(int capacidad) {
  ArregloEnteros *arreglo = malloc(sizeof(ArregloEnteros));
  arreglo->direccion = malloc(sizeof(int) * capacidad); // La capacidad no deberia ser 0 al empezar? Se modifica despues con la funcion de insertar.
  arreglo->capacidad = capacidad;
  return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros *arreglo) {
  for (int i = 0; i < arreglo->capacidad; i++) {
    free(&arreglo->direccion[i]); // Hay un problemas con los frees aca
  } 
  free(arreglo->direccion);
  free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros *arreglo, int pos) {
  return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato) {
  arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros *arreglo) {
  return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo) {
  for (int i = 0; i < arreglo->capacidad; i++) {
    printf("%d", arreglo->direccion[i]);
  }
}

void arreglo_enteros_ajustar(ArregloEnteros *arreglo, int capacidad) {
  arreglo->capacidad = capacidad;
  arreglo->direccion = realloc(arreglo->direccion, capacidad * sizeof(int));
  // Queda garbaje en memoria, modificarla si es necesaro!
}

void arreglo_enteros_insertar(ArregloEnteros *arreglo, int pos, int dato) {

  int nuevaCapacidad = arreglo->capacidad + 1;
  arreglo->direccion =
      realloc(arreglo->direccion, sizeof(int) * nuevaCapacidad);
  arreglo->capacidad = nuevaCapacidad;

  for (int i = arreglo->capacidad - 1; i > pos; i--) {
    arreglo->direccion[i] = arreglo->direccion[i - 1];
  }

  arreglo->direccion[pos] = dato;
}

void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos) {
  if (pos < 1 || pos > arreglo->capacidad) {
    printf("Error: Posición inválida.\n");
    return;
  }

  // Mueve los elementos posteriores un lugar a la izquierda
  for (int i = pos - 1; i < arreglo->capacidad - 1; i++) {
    arreglo->direccion[i] = arreglo->direccion[i + 1];
  }

  // Reduzca el tamaño del arreglo
  int nuevaCapacidad = arreglo->capacidad - 1;
  arreglo->direccion =
      realloc(arreglo->direccion, sizeof(int) * nuevaCapacidad);
  arreglo->capacidad = nuevaCapacidad;
}
