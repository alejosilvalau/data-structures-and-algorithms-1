#include "contacto.h"
#include "tablahash.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
      printf("\tInsercion exitosa, con hash: %u\n", contacto_heashear(agenda[i]));
  }

  puts("");
  printf("Contenido de la tabla:\n");
  impresion_tablahash(tabla, (FuncionVisitante)contacto_imprimir);
  puts("");

  printf("Rehash:\n");
  tablahash_redimensionar(tabla);
  for (int i = 0; i < 6; ++i) {
    printf("El contacto: ");
    contacto_imprimir(agenda[i]);
    printf(" esta en la casilla %d.\n",
           contacto_heashear(agenda[i]) % tablahash_capacidad(tabla));
  }

  puts("");
  printf("Nuevo Contenido de la tabla:\n");
  impresion_tablahash(tabla, (FuncionVisitante)contacto_imprimir);
  puts("");
  
  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 6; ++i)
    contacto_destruir(agenda[i]);

  return 0;
}