#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitanteVoid visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

/*
GList glist_eliminar(GList lista, int posicion) {
  if (posicion == 0) {
    GNode* temp = lista;
    lista = lista->next;
    free(temp);
  } else {
    int cont = 0;
    GNode* nodo = lista;
    for (; nodo != NULL && cont < posicion - 1; cont++, nodo = nodo->next);
    if (nodo != NULL && nodo->next != NULL) {
      GNode* temp = nodo->next;
      nodo->next = nodo->next->next;
      free(temp);
    }
  }
  return lista;
}
*/

void glist_eliminar(GList *lista, int posicion) {
  if (*lista == NULL) {
    return; // La lista está vacía, no hay nada que eliminar
  }

  GNode *nodo_actual = *lista;
  GNode *nodo_anterior = NULL;

  // Avanzamos hasta la posición deseada
  for (int i = 0; i < posicion; i++) {
    if (nodo_actual == NULL) {
      return; // La posición está fuera de los límites de la lista
    }
    nodo_anterior = nodo_actual;
    nodo_actual = nodo_actual->next;
  }

  if (nodo_anterior == NULL) {
    // La posición a eliminar es la primera de la lista
    *lista = nodo_actual->next;
  } else {
    nodo_anterior->next = nodo_actual->next;
  }

  // Liberamos la memoria del nodo eliminado
  free(nodo_actual);
}
