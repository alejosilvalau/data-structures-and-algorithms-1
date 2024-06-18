#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*FuncionVisitante)(int dato);
typedef int (*FuncionVisitante2)(int dato1, int dato2);

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

// ejercicio 3

/**
 * btree_nnodos: que retorne el numero de nodos del arbol.
 */
int btree_nnodos(BTree arbol);

// buscar

/**
 * btree_buscar: que devuelve 1 si el valor se encuentra en el árbol,
 * 0 en caso contrario.
 */
int btree_buscar(BTree arbol, int entero);

/**
 * btree_copiar: devuelve la copia de un arbol.
 */

BTree btree_copiar(BTree arbol);

/**
 * btree_altura: devuelve la altura de un arbol
*/
 
int max(int num1, int num2);
 
int btree_altura(BTree arbol);

/**
 * btree_nnodos_profundidad: que retorne el nùmero de nodos que se encuentran a la profundidad dada.
 */
 
int btree_nnodos_profundidad(BTree arbol, int profundidad);

/**
 * btree_profundidad: que retorne la profundidad del nodo que contiene 
 * el numero dado, y -1 si el numero no se encuentra en el arbol.
 */

int btree_profundidad(BTree arbol, int dato, int prof);

/**
 * btree_sumar:  que retorne la suma total de los datos del arbol.
 */
int btree_sumar(BTree arbol);


#endif /* __BTREE_H__ */
