#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { 
  return NULL; 
}

/**
 * Destruccion de la lista.
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
int glist_vacia(GList list) { 
  return (list == NULL); 
}

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Busca un elemento en la lista.
 */
int glist_buscar(GList list, void* data, FuncionComparar comp){
  int found = 0;
  for(GNode *node = list; found == 0 && node != NULL; node = node->next)
    if (comp(node->data, data) == 0) found = 1;
  return found;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

/**
 *  Dada una lista, retorna una nueva lista con los elementos que cumplen con el predicado.
 */
GList glist_filtrar(GList list, Predicado p, FuncionCopia copy){
  GList nuevaLista = glist_crear();

  for (GNode *node = list; node != NULL; node = node->next) {
    if (p(node->data))
      nuevaLista = glist_agregar_inicio(nuevaLista, node->data, copy);
  }

  return nuevaLista;
}

GList glist_filtrarR_aux (GList list, Predicado p, FuncionCopia copy, GList filtrada){
  if (glist_vacia(list)) return filtrada;

  if (p(list->data))
    filtrada = glist_agregar_inicio(filtrada, list->data, copy);
  
  return glist_filtrarR_aux(list->next, p, copy, filtrada);
}

GList glist_filtrarR (GList list, Predicado p, FuncionCopia copy){
  GList nuevaLista = glist_crear();

  return glist_filtrarR_aux(list, p, copy, nuevaLista);
}

GList glist_filtrarR2 (GList list, Predicado p, FuncionCopia copy){
  if (glist_vacia(list)) return glist_crear();

  GList filtrada = glist_filtrarR2(list->next, p, copy);

  if (p(list->data))
    filtrada = glist_agregar_inicio(filtrada, list->data, copy);

  return filtrada;
}

