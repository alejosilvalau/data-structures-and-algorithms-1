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
  if (arbol == NULL)
    return;
  switch (orden) {
  case BTREE_RECORRIDO_PRE:
    visit(arbol->dato);
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    break;
  case BTREE_RECORRIDO_IN:
    btree_recorrer(arbol->left, orden, visit);
    visit(arbol->dato);
    btree_recorrer(arbol->right, orden, visit);
    break;
  case BTREE_RECORRIDO_POST:
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    visit(arbol->dato);
    break;
  default:
    assert(0);
  };
  return;
  return;
}

/* 
 * Funciones 
 */

static inline int max(int a, int b) { return a >= b ? a : b; }

int btree_sumar(BTree raiz) {
  if (raiz == NULL) return 0;
  int suma_izq = btree_sumar(raiz->left);
  int suma_der = btree_sumar(raiz->right);
  return raiz->dato + suma_der + suma_izq;
}

int btree_nnodos(BTree raiz) {
  if (raiz == NULL) return 0;
  int suma_izq = btree_nnodos(raiz->left);
  int suma_der = btree_nnodos(raiz->right);
  return 1 + suma_der + suma_izq;
}

int btree_buscar(BTree raiz, int dato) {
  if (raiz == NULL)
    return 0;
  else if (raiz->dato == dato)
    return 1;
  return btree_buscar(raiz->left, dato) 
      || btree_buscar(raiz->right, dato);
}

BTree btree_copiar(BTree raiz) {
  if (raiz == NULL)
    return btree_crear();
  BTree copia_izq, copia_der, copia_raiz;
  copia_izq = btree_copiar(raiz->left);
  copia_der = btree_copiar(raiz->right);
  copia_raiz = btree_unir(raiz->dato, copia_izq, copia_der);
  return copia_raiz;
}

int btree_altura(BTree raiz) {
  if (raiz == NULL)
    return -1;
  int altura_izq = btree_altura(raiz->left);
  int altura_der = btree_altura(raiz->right);
  return max(altura_izq, altura_der) + 1;
}

int btree_profundidad(BTree raiz, int dato) {
  if (raiz == NULL)
    return -1;
  else if (raiz->dato == dato)
    return 0;
  int prof_izq = btree_profundidad(raiz->left, dato);
  if (prof_izq > -1)
    return prof_izq + 1;
  int prof_der = btree_profundidad(raiz->right, dato);
  if (prof_der > -1)
    return prof_der + 1;
  return -1;
}

int btree_nnodos_profundidad(BTree raiz, int prof) {
  if (raiz == NULL || prof < 0)
    return 0;
  if (prof == 0)
    return 1;
  int nodos_prof_izq = btree_nnodos_profundidad(raiz->left, prof - 1);
  int nodos_prof_der = btree_nnodos_profundidad(raiz->right, prof - 1);
  return nodos_prof_izq + nodos_prof_der;
}

void btree_visitar_extra(BTree raiz, BTreeOrdenDeRecorrido orden,
                  FuncionVisitanteExtra visit, void* extra) {
  if (raiz == NULL)
    return;
  switch (orden) {
  case BTREE_RECORRIDO_PRE:
    visit(raiz->dato, extra);
    btree_visitar_extra(raiz->left, orden, visit, extra);
    btree_visitar_extra(raiz->right, orden, visit, extra);
    break;
  case BTREE_RECORRIDO_IN:
    btree_visitar_extra(raiz->left, orden, visit, extra);
    visit(raiz->dato, extra);
    btree_visitar_extra(raiz->right, orden, visit, extra);
    break;
  case BTREE_RECORRIDO_POST:
    btree_visitar_extra(raiz->left, orden, visit, extra);
    btree_visitar_extra(raiz->right, orden, visit, extra);
    visit(raiz->dato, extra);
    break;
  default:
    assert(0);
  };
  return;
}

// Cant. de nodos
void inc(int dato, int *extra) {
  (*extra)++;
}

int btree_nnodos_extra(BTree raiz) {
  int nnodos = 0;
  btree_visitar_extra(raiz, BTREE_RECORRIDO_PRE,
                      (FuncionVisitanteExtra) inc, &nnodos);
  return nnodos;
}

// Suma
void add(int dato, int *extra) {
  *extra += dato;
}

int btree_sumar_extra(BTree raiz) {
  int suma = 0;
  btree_visitar_extra(raiz, BTREE_RECORRIDO_PRE,
                      (FuncionVisitanteExtra) add, &suma);
  return suma;
}

// Busqueda
typedef struct {
  int objetivo;   // Entero a buscar en el arbol
  int encontrado; // Indica si se encontro o no
} Search;

void find(int dato, Search *extra) {
  // if (!extra->encontrado)
  //  extra->encontrado = dato == extra->objetivo;
  extra->encontrado = extra->encontrado || dato == extra->objetivo;
}

int btree_buscar_extra(BTree raiz, int dato) {
  Search extra = {dato, 0};
  // extra.objetivo = dato;
  // extra.encontrado = 0;
  btree_visitar_extra(raiz, BTREE_RECORRIDO_PRE,
                      (FuncionVisitanteExtra) find, &extra);
  return extra.encontrado;
}

