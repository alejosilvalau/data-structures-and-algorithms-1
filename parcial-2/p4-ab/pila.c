#include "arregloenteros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Pila {
  ArregloEnteros *arr;
  int ultimo;
};
typedef struct _Pila *Pila;

Pila pila_crear(int capacidad) {
  Pila nuevaPila = malloc(sizeof(struct _Pila));

  nuevaPila->arr = arreglo_enteros_crear(capacidad);
  nuevaPila->ultimo = -1;

  return nuevaPila;
}

void pila_destruir(Pila pila) {
  arreglo_enteros_destruir(pila->arr);
  free(pila);
}

int pila_vacia(Pila pila) { return (pila->ultimo == -1); }

int pila_tope(Pila pila) { return pila->arr->direccion[pila->ultimo]; }

void pila_apilar(Pila pila, int dato) {
  if (pila->ultimo == pila->arr->capacidad - 1) {
    arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad * 2);
  }
  pila->ultimo++;
  pila->arr->direccion[pila->ultimo] = dato;
}

void pila_desapilar(Pila pila) {
  pila->arr->direccion[pila->ultimo] = 0;
  pila->ultimo--;
}

void pila_imprimir(Pila pila) { arreglo_enteros_imprimir(pila->arr); }