#ifndef __GSTACK_H__
#define __GSTACK_H__
#include "glist.h"

typedef GList Pila;

/**
 * Crea una pila vacia
 */
Pila pila_crear();

/**
 * Destrucción de una pila
 */
void pila_destruir(Pila pila, FuncionDestructora destroy);

/**
 * Devuelve el último elemento de una pila
 */
void *pila_tope(Pila pila);

/**
 * Determina si una pila es vacía o no
 */
int pila_es_vacia(Pila pila);

/**
 * Agrega un elemento a la pila
 */
void *pila_apilar(Pila *pila, void *dato, FuncionCopia copy);

/**
 * Quita el último elemento insertado en la pila
 */
void pila_desapilar(Pila *pila);

/**
 * Imprime la pila
 */
void pila_imprimir(Pila pila, FuncionVisitanteVoid imprimir);

#endif /* __GSTACK_H__ */
