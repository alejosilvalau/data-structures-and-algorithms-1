#include "tablahash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct _CasillaHash {
  void *dato;
  struct _CasillaHash *next;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].next = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    if (tabla->elems[idx].dato != NULL) {
      // Cada elemento tiene que destruirse apuntando al siguiente
      // Los elementos tienen que quedar de la forma dato == NULL and next == NULL
      // El primer elemento se iguala en NULL en ambos campos cuando se sale del while
    }
    
    // if (tabla->elems[idx].next != NULL) {
    //   CasillaHash *casillaEliminar;
    //   while (tabla->elems[idx].dato != NULL) {
    //     casillaEliminar = &tabla->elems[idx];
    //     tabla->elems[idx] = tabla->elems[idx].next;
    //     tabla->destr(casillaEliminar->dato);
    //     free(casillaEliminar);
    //   }
    // }
  }
  free(tabla->elems);
  free(tabla);
  return;
}


/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }
  // La casilla no esta libre, hay que buscar si el dato ya esta en la lista.
  CasillaHash *casilla = &tabla->elems[idx];
  for (; casilla->next != NULL; casilla = casilla->next) {
    if (tabla->comp(casilla->next->dato, dato) == 0) {
      tabla->destr(casilla->next->dato);
      casilla->next->dato = tabla->copia(dato);
      return;
    }
  }
  // Si el dato no esta en la tabla, entonces agregarlo al
  // final de la lista en el indice indicado.
  tabla->numElems++;
  casilla->next = malloc(sizeof(CasillaHash));
  assert(casilla->next != NULL);
  casilla->next->dato = tabla->copia(dato);
  casilla->next->next = NULL;
  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;
  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return NULL;
  // Devolver el dato si el mismo ya se encontraba en la tabla recorriendo la
  // lista.
  for (CasillaHash *casilla = &tabla->elems[idx]; casilla != NULL;
       casilla = casilla->next) {
    if (tabla->comp(casilla->dato, dato) == 0) {
      return casilla->dato;
    }
  }
  // En el caso que no este el dato en la lista, se retorna NULL.
  return NULL;
}


/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;

  // Si el primer elemento de la lista es el dato a eliminar, eliminarlo.
  if ((tabla->comp(tabla->elems[idx].dato, dato) == 0) &&
      tabla->elems[idx].next == NULL) {
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }

  for (CasillaHash *casilla = &tabla->elems[idx]; casilla->next != NULL;
       casilla = casilla->next) {
    // Si se encuentra el dato en la lista, se elimina
    if (tabla->comp(casilla->next->dato, dato) == 0) {
      tabla->numElems--;
      CasillaHash *casillaEliminar = casilla->next;
      casilla->next = casillaEliminar->next;
      tabla->destr(casillaEliminar->dato);
      free(casillaEliminar);
      return;
    }
  }
}
