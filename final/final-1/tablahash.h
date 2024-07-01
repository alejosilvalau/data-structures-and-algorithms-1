#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "tipos.h"

typedef struct _CasillaHash {
  void *dato;
  struct _CasillaHash *sig;
} CasillaHash;

typedef struct {
  CasillaHash *elems;
  unsigned capacidad;
  FuncionHashear hashear;
  FuncionCopiar copiar;
  FuncionComparar comparar;
} TablaHash;

/**
* Crea una nueva tabla.
*/
TablaHash *tablahash_crear(unsigned capacidad, FuncionHashear hashear,
 FuncionCopiar copiar, FuncionComparar comparar);

/**
* Inserta un nuevo dato en la tabla.
*/
void tablahash_insertar(TablaHash *tabla, void *dato);

/**
* Devuelve 0 si el usuario no esta. ! en caso contrario
*/
int tablahash_buscar(TablaHash *tabla, void *dato);

#endif /* __TABLAHASH_H__ */