#include "contacto.h"
#include "tablahash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// gcc -Wall contacto.c tablahash.c test2.c utils.c -g -o main
// valgrind ./main

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

#define CAPACIDAD_INICIAL 11
/** Capacidad inicial para la tabla hash */

/**
 * Caso de prueba: Tabla hash para contactos
 */
int main() {

  // Iniciar tabla hash
  TablaHash tabla = tablahash_crear(
      CAPACIDAD_INICIAL, (FuncionCopiadora)contacto_copia,
      (FuncionComparadora)contacto_comparar,
      (FuncionDestructora)contacto_destruir, (FuncionHash)contacto_heashear);

  // Contactos
  Contacto *agenda[6];
  agenda[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  agenda[1] = contacto_crear("Moni Argento", "3412684759", 60);
  agenda[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  agenda[3] = contacto_crear("Paola Argento", "3416259862", 29);
  agenda[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  agenda[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Insertando el contacto: ");
    contacto_imprimir(agenda[i]);
    printf(" en la casilla %d.\n",
           contacto_heashear(agenda[i]) % tablahash_capacidad(tabla));
    int nElems = tablahash_nelems(tabla);
    tablahash_insertar(tabla, agenda[i]);
    if (tablahash_nelems(tabla) == nElems)
      printf("\tInsercion fallida: Colision.\n");
    else
      printf("\tInsercion exitosa.\n");
  }
  puts("");
  contacto_imprimir(tabla->elems[10].next->dato);
  puts("");
}