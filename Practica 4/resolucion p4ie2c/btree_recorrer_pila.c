#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "pila.h"

/**
 * Recorrido DFS en preorden del arbol usando una pila general
 * ===========================================================
 *
 * En este ejercicio, al apilar los nodos del árbol, no se realizaran copias
 * fisicas de los mismos, dado que en la función btree_recorrer_pila el uso que
 * vamos a darles es momentaneo y no vamos a modificarlos en ningún momento.
 * Por el contrario, si realizaramos copias físicas de los mismos, por ejemplo
 * con una función como:
 * BTree btree_copiar(BTree nodo) {
 *   if (nodo == NULL)
 *     return NULL;
 *   BTree copy = btree_unir(nodo->dato, NULL, NULL);
 *   copy->left = btree_copiar(nodo->left);
 *   copy->right = btree_copiar(nodo->right);
 *   return copy;
 * }
 * cada vez que se apilara un nodo, se realizaria una copia fisica de todo el
 * subarbol correspondiente a ese nodo. Lo cual no tiene sentido para el uso
 * que le estamos dando.
 */

/**
 * Funciones usadas para copiar y destruir datos en la pila respectivamente.
 * Notar que id retorna el mismo puntero, es decir no realiza una copia fisica
 * del dato, y null no libera memoria.
 */

static void *id(void* data) { return data; }
static void null(__attribute__((unused)) void *data) { return; }


/**
 * Recorre el arbol de forma iterativa en un orden dado por el parametro 'orden'
 * aplicando la FuncionVisitante 'visit' a cada uno de los elementos.
 */
void btree_recorrer_pila(BTree nodo, BTreeOrdenDeRecorrido orden,
                         void (*visit)(int dato)) {
  if (nodo == NULL)
    return;
  Pila pila = pila_crear();
  BTree current_node;
  if (orden == BTREE_RECORRIDO_PRE) {
    pila = pila_apilar(pila, (void *) nodo, id);
    while (!pila_es_vacia(pila)) {
      current_node = (BTree) pila_ultimo(pila);
      pila = pila_desapilar(pila, null);
      visit(current_node->dato);
      if (current_node->right != NULL) {
        pila = pila_apilar(pila, (void *) current_node->right, id);
      }
      if (current_node->left != NULL) {
        pila = pila_apilar(pila, (void *) current_node->left, id);
      }
    }
    pila_destruir(pila, null);
  } else if (orden == BTREE_RECORRIDO_IN || orden == BTREE_RECORRIDO_POST) {
    printf("Orden no implementado");
  } else
    printf("Orden invalido");

  return;
}
