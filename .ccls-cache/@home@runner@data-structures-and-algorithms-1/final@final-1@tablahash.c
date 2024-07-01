#include "tablahash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

TablaHash *tablahash_crear(unsigned capacidad, FuncionHashear hashear,
                           FunctionCopiar copiar, FunctionComparar comparar) {
  TablaHash *tabla = malloc(sizeof(TablaHash));
  assert(tabla != NULL);

  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);

  tabla->capacidad = capacidad;

  tabla->hashear = hashear;
  tabla->copiar = copiar;
  tabla->comparar = comparar;

  for (unsigned idx = 0; idx < capacidad; idx++) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].sig = NULL;
  }

  return tabla;
}

void tablahash_insertar(TablaHash *tabla, void *dato) {
  // Si esta vacia, instertar directamente
  // Si ya hay valor, instertar al final

  unsigned idx = tabla->hashear(dato) % tabla->capacidad;

  // Si la casilla esta vacia, insertar dato
  if (tabla->elems[idx].dato == NULL) {
    tabla->elems[idx].dato = tabla->copiar(dato);
    printf("El dato se ingreso en una celda vacia \n");
    return;
  }

  // Si la casilla no esta libre, comparamos el los datos 
  // para verificar si el dato no esta ya en la tabla
  CasillaHash *casillaActual = &tabla->elems[idx];
  for (; casillaActual->sig != NULL; casillaActual = casillaActual->sig) {
    if (tabla->comparar(casillaActual->dato, dato) == 0) {
      printf("El dato ya existe en la tabla \n");
      return;
    }
  }
  
  // Verificamos que el dato no sea el ultimo
  if (tabla->comparar(casillaActual->dato, dato) == 0) {
    printf("El dato ya existe en la tabla \n");
    return;
  }

  // El dato no esta en la tabla, se agrega al final de la lista
  casillaActual->sig = malloc(sizeof(CasillaHash));
  assert(casillaActual->sig);
  casillaActual->sig->dato = tabla->copiar(dato);
  casillaActual->sig->sig = NULL;
  printf("El dato se ingreso al final de una celda ya ocupada\n");
}

int tablahash_buscar(TablaHash *tabla, void *dato) {
  // Calcula el indice donde deveria estar el dato
  unsigned idx = tabla->hashear(dato) % tabla->capacidad;

  // Si la casilla esta vacia, el dato no esta
  if (tabla->elems[idx].dato == NULL)
    return 0;

  CasillaHash *casillaActual = &tabla->elems[idx];
  // Comprobamos si el dato es el ultimo en el encadenamiento de casillas
  for (; casillaActual != NULL; casillaActual = casillaActual->sig)
    if (tabla->comparar(casillaActual->dato, dato) == 0)
      return 1;
  return 0;
}
