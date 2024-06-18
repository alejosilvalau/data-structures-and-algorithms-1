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
  case BTREE_RECORRIDO_IN:
    btree_recorrer(arbol->left, orden, visit);
    visit(arbol->dato);
    btree_recorrer(arbol->right, orden, visit);
    break;
  case BTREE_RECORRIDO_PRE:
    visit(arbol->dato);
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    break;
  case BTREE_RECORRIDO_POST:
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    visit(arbol->dato);
    break;
  }
  return;
}

int btree_nnodos(BTree arbol) {
  int cont = 0;
  if (arbol == NULL) {
    return cont;
  } else {
    cont += 1;

    cont += btree_nnodos(arbol->left);
    cont += btree_nnodos(arbol->right);
  }
  return cont;
}

int btree_buscar(BTree arbol, int entero) {
  if (arbol == NULL) {
    return 0;
  }

  if (arbol->dato == entero) {
    return 1;
  }
  int encontrado_izquierdo = btree_buscar(arbol->left, entero);
  int encontrado_derecho = btree_buscar(arbol->right, entero);

  return (encontrado_izquierdo || encontrado_derecho);
}

BTree btree_copiar(BTree arbol) {
  BTree nuevoArbol = btree_crear();

  if (arbol == NULL) {
    return nuevoArbol;
  }
  nuevoArbol = btree_unir(arbol->dato, btree_copiar(arbol->left),
                          btree_copiar(arbol->right));
  return nuevoArbol;
}

int max(int num1, int num2) {
  if (num1 > num2) {
    return num1;
  } else {
    return num2;
  }
}

int btree_altura(BTree arbol) {
  int altura;
  if (arbol == NULL) {
    altura = -1;
    return altura;
  } else {
    int altura_izq = btree_altura(arbol->left);
    int altura_der = btree_altura(arbol->right);
    return max(altura_izq, altura_der) + 1;
  }
}

int btree_nnodos_profundidad(BTree arbol, int profundidad) {
  if (arbol == NULL) {
    return 0;
  } else if (profundidad == 0) {
    return 1;
  } else {
    return btree_nnodos_profundidad(arbol->left, profundidad - 1) +
           btree_nnodos_profundidad(arbol->right, profundidad - 1);
  }
}

int btree_profundidad(BTree arbol, int dato) {
  if (arbol == NULL) {
    return -1;
  }
  if (arbol->dato == dato) {
    return 0;
  }
  int left_depth = btree_profundidad(arbol->left, dato);
  if (left_depth != -1) {
    return left_depth + 1;
  }
  int right_depth = btree_profundidad(arbol->right, dato);
  if (right_depth != -1) {
    return right_depth + 1;
  }
  return -1;
}

int btree_sumar(BTree arbol) {
  if (arbol == NULL) {
    return 0;
  } else {
    return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
  }
}

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra) {
  if (arbol == NULL) {
    return;
  }
  if (orden == BTREE_RECORRIDO_IN) {
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
  } else if (orden == BTREE_RECORRIDO_PRE) {
    visit(arbol->dato, extra);
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
  } else if (orden == BTREE_RECORRIDO_POST) {
    btree_recorrer_extra(arbol->left, orden, visit, extra);
    btree_recorrer_extra(arbol->right, orden, visit, extra);
    visit(arbol->dato, extra);
  }
  return;
}
