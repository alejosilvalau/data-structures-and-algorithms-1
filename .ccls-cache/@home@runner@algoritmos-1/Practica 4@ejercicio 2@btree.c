#include "btree.h"
#include "gstack.h"
#include <assert.h>
#include <stdlib.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  if (orden == BTREE_RECORRIDO_IN){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_PRE){
    if (arbol == NULL) { 
      return;
    }
    else {
      visit(arbol->dato);
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_POST){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
    }
  }
  return;
}

// ejercicio 2c

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
    pila_apilar(pila, (void *) nodo, id);
    while (!pila_es_vacia(pila)) {
      current_node = (BTree) pila_ultimo(pila);
      pila_desapilar(pila);
      visit(current_node->dato);
      if (current_node->right != NULL) {
        pila_apilar(pila, (void *) current_node->right, id);
      }
      if (current_node->left != NULL) {
        pila_apilar(pila, (void *) current_node->left, id);
      }
    }
    pila_destruir(pila, null);
  } else if (orden == BTREE_RECORRIDO_IN || orden == BTREE_RECORRIDO_POST) {
    printf("Orden no implementado");
  } else
    printf("Orden invalido");

  return;
}