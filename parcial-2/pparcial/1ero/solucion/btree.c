#include "btree.h"
#include "cola.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

BTree btree_crear() { return NULL; }

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

static void no_destruir_data(void *data) { return; }
static void *no_copia_data(void *data) { return data; }

void btree_foreach(BTree root, FuncionVisitanteExtra visit, void *extra) {
  Cola cola = cola_crear();

  if (root != NULL) {
    cola = cola_encolar(cola, root, no_copia_data);
  } else {
    return;
  }
  int profundidad = 0;

  while (!cola_es_vacia(cola)) {
    int cantNodosProfundidadActual = cola_longitud(cola);
    int profundidadActual = 0;
    
    while (profundidadActual < cantNodosProfundidadActual) {
      BTree actual = cola_inicio(cola);
      cola = cola_desencolar(cola, no_destruir_data);

      visit(actual->dato, (int*)extra);

      if (actual->left != NULL) {
        cola = cola_encolar(cola, actual->left, no_copia_data);
      }
      if (actual->right != NULL) {
        cola = cola_encolar(cola, actual->right, no_copia_data);
      }
      profundidadActual++;
    }
    profundidad++;
  }

  cola_destruir(cola, no_destruir_data);
}
