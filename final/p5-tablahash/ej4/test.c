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
  Contacto *agenda[20];
  agenda[0] = contacto_crear("Aepe Argento", "3412695452", 61);
  agenda[1] = contacto_crear("Boni Argento", "3412684759", 60);
  agenda[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  agenda[3] = contacto_crear("Daola Argento", "3416259862", 29);
  agenda[4] = contacto_crear("Earia Elena Fuseneco", "3416874594", 59);
  agenda[5] = contacto_crear("Fardo Fuseneco", "3416894526", 64);
  agenda[6] = contacto_crear("Garlos Baldomir", "3412789654", 52);
  agenda[7] = contacto_crear("Huciana Aymar", "3415678902", 45);
  agenda[8] = contacto_crear("Iionel Messi", "3412345678", 35);
  agenda[9] = contacto_crear("Jabriela Sabatini", "3418765432", 51);
  agenda[10] = contacto_crear("Kanu Ginóbili", "3416543210", 46);
  agenda[11] = contacto_crear("Lenata Notni", "3412789456", 33);
  agenda[12] = contacto_crear("Mduardo Sacheri", "3415678123", 53);
  agenda[13] = contacto_crear("Picardo Darín", "3412349087", 65);
  agenda[14] = contacto_crear("Ooledad Pastorutti", "3418762543", 41);
  agenda[15] = contacto_crear("Pustavo Santaolalla", "3416549087", 70);
  agenda[16] = contacto_crear("Qauricio Macri", "3412785643", 64);
  agenda[17] = contacto_crear("Rristina Fernández", "3415673452", 69);
  agenda[18] = contacto_crear("Slberto Fernández", "3412345670", 63);
  agenda[19] = contacto_crear("Uarcelo Tinelli", "3418765439", 62);
  


  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 20; ++i) {
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

  // printf("Rehash:\n");
  // tablahash_redimensionar(tabla);
  // for (int i = 0; i < 6; ++i) {
  //   printf("El contacto: ");
  //   contacto_imprimir(agenda[i]);
  //   printf(" esta en la casilla %d.\n",
  //          contacto_heashear(agenda[i]) % tablahash_capacidad(tabla));
  // }

  // puts("");
  // printf("Nuevo Contenido de la tabla:\n");
  // impresion_tablahash(tabla, (FuncionVisitante)contacto_imprimir);
  // puts("");
  
  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 20; ++i)
    contacto_destruir(agenda[i]);

  return 0;
}