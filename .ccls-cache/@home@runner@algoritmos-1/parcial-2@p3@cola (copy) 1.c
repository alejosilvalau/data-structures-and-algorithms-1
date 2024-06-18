include "cola.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

// gcc -Wall cola.c glist.c -g -o main
// ./main

Cola cola_crear() {
  Cola cola = malloc(sizeof(struct _GList));
  cola->first = NULL;
  cola->last = NULL;
  return cola;
}

void cola_destruir(Cola cola, FuncionDestructora destroy) {
  glist_destruir_node(cola->first, destroy);
  free(cola);
}

int cola_es_vacia(Cola cola) { return (cola->first == NULL); }

void *cola_inicio(Cola cola) {
  if (!(cola_es_vacia(cola))) {
    return cola->first->data;
  }
  return NULL;
}

Cola cola_encolar(Cola cola, void *dato, FuncionCopia copy) {
  GNode *nuevoNodo = malloc(sizeof(GNode));
  nuevoNodo->next = NULL;
  nuevoNodo->data = copy(dato);

  if (!(cola_es_vacia(cola))) {
    cola->last->next = nuevoNodo;
  } else {
    cola->first = nuevoNodo;
  }
  cola->last = nuevoNodo;
  return cola;
}

Cola cola_desencolar(Cola cola, FuncionDestructora destroy) {
  if (!(cola_es_vacia(cola))) {
    GNode *nodoElminar = cola->first;

    cola->first = cola->first->next;
    if (cola->first == NULL) {
      cola->last = NULL;
    }
    destroy(nodoElminar->data);
    free(nodoElminar);
    return cola;
  }
  return NULL;
}

void cola_imprimir(Cola cola, FuncionVisitante visit) {
  for (GNode *node = cola->first; node != NULL; node = node->next)
    visit(node->data);
}