#include "gstack.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

Pila pila_crear() { return NULL; }

void pila_destruir(Pila pila, FuncionDestructora destroy) {
  glist_destruir(pila, destroy);
}

int pila_es_vacia(Pila pila) { return glist_vacia(pila); }

void *pila_tope(Pila pila) {
  GNode *nodo = pila;
  return nodo->data;
}

void *pila_apilar(Pila *pila, void *dato, FuncionCopia copy) {
  *pila = glist_agregar_inicio(*pila, dato, copy);
  return (void *)pila;
}

void pila_desapilar(Pila *pila) { glist_eliminar(pila, 0); }

void pila_imprimir(Pila pila, FuncionVisitanteVoid imprimir) {
  glist_recorrer(pila, imprimir);
}
