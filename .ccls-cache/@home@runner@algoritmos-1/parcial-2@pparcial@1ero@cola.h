#ifndef __PILA_H__
#define __PILA_H__

#include "glist.h"
#include "tipos.h"

typedef struct _GList *Cola; // una definicion equivalente: typedef GList Cola;

/**
 * Devuelve una cola vacia.
 */
Cola cola_crear();

/**
 * Destruccion de la cola.
 */
void cola_destruir(Cola cola, FuncionDestructora);

/**
 * Determina si la cola es vacía.
 */
int cola_es_vacia(Cola cola);

/**
 * Devuelve el elemento en el frente de la cola sin eliminarlo.
 */
void *cola_inicio(Cola cola);

/**
 * Agrega un elemento al final de la cola.
 */
Cola cola_encolar(Cola cola, void *dato, FuncionCopia);

/**
 * Devuelve el elemento en el frente de la cola eliminandolo.
 */
Cola cola_desencolar(Cola cola, FuncionDestructora);

/**
 * Imprime la cola en pantalla.
 */
void cola_imprimir(Cola cola, FuncionVisitante);

/**
 * Devuelve la cantidad de elementos en la cola.
 */
int cola_longitud(Cola cola);

#endif /* __PILA_H__ */