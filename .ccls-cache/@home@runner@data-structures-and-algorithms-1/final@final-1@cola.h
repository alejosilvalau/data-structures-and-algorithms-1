#ifndef __COLA_H__
#define __COLA_H__

#include "tipos.h"

typedef struct _CNodo {
  void *dato;
  struct _CNodo *sig;
} CNodo;

typedef struct {
  CNodo *inicio;
  CNodo *final;
  FuncionComparar comparar;
  FuncionComparar comparar_aux;
  FuncionCopiar copiar;
  FuncionDestruir destruir;
  FuncionVisitar visitar;
} Cola;

/**
 * Crea una nueva cola.
 */
Cola *cola_crear(FuncionComparar comparar, FuncionComparar comparar_aux,
                 FuncionCopiar copiar, FuncionDestruir destruir,
                 FuncionVisitar visitar);

/**
 * Encola un nuevo elemento en la posicion indicada.
 */
Cola *cola_encolar(Cola *cola, void *dato);

/**
 * Imprime el proximo elemento en la cola.
 */
void cola_proximo(Cola *cola);

/**
 * Imprime todos los elementos de la cola.
 */
void cola_imprimir(Cola *cola);

/**
 * Elimina el elemento indicado de la cola. Si en dato pasado como
 * argumento es NULL, entonces se elimina el primer elemento.
 */
Cola *cola_desencolar(Cola *cola, void *dato);

/**
 * Retorna 1 si la cola esta vacia, 0 en caso contrario
 */

int cola_vacia(Cola *cola);

#endif /* __COLA_H__ */