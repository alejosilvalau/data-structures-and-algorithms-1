#ifndef __GTREE_H__
#define __GTREE_H__

typedef void *(*FuncionCopiadora)(void *);
typedef void (*FuncionDestructora)(void *);
typedef void (*FuncionVisitanteExtra)(void *, void *);
typedef int (*FuncionComparadora)(void *, void *);

typedef struct _GTNodo *GTree;

/**
 * Devuelve un arbol general vacio.
 */
GTree gtree_crear();

/**
 * Determina si el arbol es vacio.
 */
int gtree_vacio(GTree arbol);

/**
 * Destruye el arbol.
 */
void gtree_destruir(GTree arbol, FuncionDestructora destr);

/**
 * Agrega un nodo hoja al arbol con el dato dado. El nuevo nodo se agrega como
 * hijo del nodo del arbol cuyo dato coincida con datoPadre. Si el arbol es
 * vacio, entonces el dato se agrega en el nodo raiz.
 */
GTree gtree_agregar(GTree arbol, void *datoPadre, void *dato,
                    FuncionCopiadora copiar, FuncionComparadora comp);

/**
 * Recorrido del arbol.
 */
void gtree_recorrer_extra(GTree arbol, FuncionVisitanteExtra visit,
                          void *extra);

/**
 * Retorna el numero de nodos del arbol.
 */
int gtree_nnodos(GTree arbol);

#endif /** __GTREE_H__ */