#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);
typedef void (*FuncionVisitanteExtra)(int dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra);

/**
 * Numero de nodos del arbol.
 */
int btree_nnodos(BTree arbol);
int btree_nnodos2(BTree arbol);

/**
 * Buscar un dato en el arbol, devuelve 1 si esta y 0 sino.
 */
int btree_buscar(BTree arbol, int dato);
int btree_buscar2(BTree arbol, int dato);
int btree_buscar3(BTree arbol, int dato);

/**
 * Retorna una copia del arbol.
 */
BTree btree_copiar(BTree arbol);

/**
 * Profundidad del nodo que contiene el dato dado, y -1 si no se encuentra.
 */
int btree_profundidad(BTree arbol, int dato);

#endif /* __BTREE_H__ */
