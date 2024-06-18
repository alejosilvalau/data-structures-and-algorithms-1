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

/**
 * Devuelve la cantidad de nodos del arbol.
 */
int btree_nnodos(BTree arbol);

/**
 * Devuelve si el entero se encuntra en el arbol con un 1. Devuelve un 0 si no
 * esta
 */
int btree_buscar(BTree arbol, int entero);

/**
 * Devuelve una copia del arbol.
 */
BTree btree_copiar(BTree arbol);

/**
 * Devuelve la altura del arbol.
 */
int btree_altura(BTree arbol);

/**
 * Devuelve los numeros de nodos del arbol para la profundidad indicada.
 */
int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * Devuelve la profundidad del nodo indicado.
 */
int btree_profundidad(BTree arbol, int dato);

/**
 * Devuelve la suma total de los datos del arbol.
 */
int btree_sumar(BTree arbol);

/**
 * Recorrido del arbol, utilizando la funcion pasada con el orden indicado por
 * parametros.
 */
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,
                          FuncionVisitanteExtra visit, void *extra);

#endif /* __BTREE_H__ */
