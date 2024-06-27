#include "btree.h"
#include <assert.h>
#include <stdio.h>
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
  if (orden == BTREE_RECORRIDO_IN) {
    if (arbol == NULL) {
      return;
    } else {
      btree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_PRE) {
    if (arbol == NULL) {
      return;
    } else {
      visit(arbol->dato);
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_POST) {
    if (arbol == NULL) {
      return;
    } else {
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
    }
  }
  return;
}

// ejercicio 3

int btree_nnodos(BTree arbol) {
  int n = 0;
  if (arbol == NULL) {
    return n;
  } else {
    n += 1;
    printf("%d\n", arbol->dato);
    n += btree_nnodos(arbol->left);
    n += btree_nnodos(arbol->right);
  }
  return n;
}

// buscar

int btree_buscar(BTree arbol, int entero) {
  if (arbol == NULL) {
    return 0; // El árbol está vacío, no se encuentra el entero
  }

  if (arbol->dato == entero) {
    return 1; // Se encontró el entero en el nodo actual
  }

  // Buscar en el subárbol izquierdo y derecho recursivamente
  int encontrado_izquierdo = btree_buscar(arbol->left, entero);
  int encontrado_derecho = btree_buscar(arbol->right, entero);

  // Devolver 1 si se encuentra en alguno de los subárboles
  return (encontrado_izquierdo || encontrado_derecho);
}

// comparar

BTree btree_copiar(BTree arbol) {
  BTree narbol = btree_crear();

  if (arbol == NULL) {
    return narbol;
  }

  else {
    narbol = btree_unir(arbol->dato, btree_copiar(arbol->left),
                        btree_copiar(arbol->right));
  }

  return narbol;
}

// altura

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

// nodos en profundidad n

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

// profundidad

int btree_profundidad(BTree arbol, int dato, int prof) {
  if (arbol == NULL) {
    return -1;
  }
  if (arbol->dato == dato) {
    return prof;
  }
  int n = btree_profundidad(arbol->left, dato, prof + 1);
  if (n == -1) {
    return btree_profundidad(arbol->right, dato, prof + 1);
  } else {
    return n;
  }
}

// sumar

int btree_sumar(BTree arbol) {
  if (arbol == NULL) {
    return 0;
  } else {
    return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
  }
}

// ejercicio 4.a

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra) {
  if (orden == BTREE_RECORRIDO_IN) {
    if (arbol == NULL) {
      return;
    } else {
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
    }
  }
  if (orden == BTREE_RECORRIDO_PRE) {
    if (arbol == NULL) {
      return;
    } else {
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
    }
  }
  if (orden == BTREE_RECORRIDO_POST) {
    if (arbol == NULL) {
      return;
    } else {
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
      visit(arbol->dato, extra);
    }
  }
  return;
}
