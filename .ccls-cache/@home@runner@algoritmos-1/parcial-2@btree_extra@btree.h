#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);
typedef void (*FuncionVisitanteExtra)(int, void*);

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


int btree_sumar(BTree raiz);
int btree_nnodos(BTree raiz);
int btree_buscar(BTree raiz, int dato);
BTree btree_copiar(BTree raiz);
int btree_altura(BTree raiz);
int btree_profundidad(BTree raiz, int dato);
int btree_nnodos_profundidad(BTree raiz, int prof);
void btree_visitar_extra(BTree raiz, BTreeOrdenDeRecorrido orden,
                  FuncionVisitanteExtra visit, void* extra);

int btree_nnodos_extra(BTree raiz);
int btree_sumar_extra(BTree raiz);
int btree_buscar_extra(BTree raiz, int dato);

#endif /* __BTREE_H__ */
