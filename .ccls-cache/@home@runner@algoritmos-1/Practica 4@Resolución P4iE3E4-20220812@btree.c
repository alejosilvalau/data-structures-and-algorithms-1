#include "btree.h"
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
  if (btree_empty(arbol))
    return;
  if (orden == BTREE_RECORRIDO_PRE)
    visit(arbol->dato);
  btree_recorrer(arbol->left, orden, visit);
  if (orden == BTREE_RECORRIDO_IN)
    visit(arbol->dato);
  btree_recorrer(arbol->right, orden, visit);
  if (orden == BTREE_RECORRIDO_POST)
    visit(arbol->dato);
}
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra) {
  if (btree_empty(arbol))
    return;
  if (orden == BTREE_RECORRIDO_PRE)
    visit(arbol->dato, extra);
  btree_recorrer_extra(arbol->left, orden, visit, extra);
  if (orden == BTREE_RECORRIDO_IN)
    visit(arbol->dato, extra);
  btree_recorrer_extra(arbol->right, orden, visit, extra);
  if (orden == BTREE_RECORRIDO_POST)
    visit(arbol->dato, extra);
}

/**
 * Numero de nodos del arbol.
 */

int btree_nnodos(BTree arbol) {
  if (btree_empty(arbol))
    return 0;
  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

// Funcion visitante que incrementa en 1 el contador cada vez que es llamada
// Compilar con -Wno-unused-parameter
void visit_nnodos(int dato, int *contador) { ++*contador; }

int btree_nnodos2(BTree arbol) {
  int n = 0; // Todos las llamadas acceden a la misma direccion
             // de memoria que guarda el contador n
  btree_recorrer_extra(arbol, BTREE_RECORRIDO_PRE,
                       (FuncionVisitanteExtra)visit_nnodos, &n);
  return n;
}

/**
 * Buscar un dato en el arbol, devuelve 1 si esta y 0 sino.
 */

int btree_buscar(BTree arbol, int dato) {
  if (btree_empty(arbol))
    return 0;
  if (arbol->dato == dato)
    return 1;
  if (btree_buscar(arbol->left, dato))
    return 1;
  return btree_buscar(arbol->right, dato);
}

int btree_buscar2(BTree arbol, int dato) {
  if (btree_empty(arbol))
    return 0;
  return arbol->dato == dato || btree_buscar2(arbol->left, dato) ||
         btree_buscar2(arbol->right, dato);
}

// Estructura con el dato buscado y una bandera para indicar si se encuentra
typedef struct {
  int datoBuscado;
  int encontrado;
} Contenedor;

// Funcion visitante que compara el dato actual con el dato buscado y activa la
// bandera si hay coincidencia
void visit_buscar(int dato, Contenedor *c) {
  if (dato == c->datoBuscado && c->encontrado == 0)
    c->encontrado = 1;
}

// Recorre TODOS los nodos del arbol, es decir, no deja de recorrer cuando
// encuentra el dato buscado
int btree_buscar3(BTree arbol, int dato) {
  Contenedor c = {dato, 0};
  btree_recorrer_extra(arbol, BTREE_RECORRIDO_PRE,
                       (FuncionVisitanteExtra)visit_buscar, &c);
  return c.encontrado;
}

/**
 * Retorna una copia del arbol.
 */
BTree btree_copiar(BTree arbol) {
  if (btree_empty(arbol))
    return btree_crear();
  return btree_unir(arbol->dato, btree_copiar(arbol->left),
                    btree_copiar(arbol->right));
}

/**
 * Profundidad del nodo que contiene el dato dado, y -1 si no se encuentra.
 */
int btree_profundidad(BTree arbol, int dato) {
  if (btree_empty(arbol))
    return -1;
  if (arbol->dato == dato)
    return 0;
  int k = btree_profundidad(arbol->left, dato);
  if (k == -1)
    k = btree_profundidad(arbol->right, dato);
  return k == -1 ? -1 : k + 1;
}