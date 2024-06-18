#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int es_mayor_de(void *dato) { return contacto_es_mayor_de(dato, 60); }

void *f_copia_contacto(void *dato) { return contacto_copia((Contacto *)dato); }

void f_imprimir_contacto(void *dato) { contacto_imprimir((Contacto *)dato); }

void f_dest_contacto(void *dato) { contacto_destruir((Contacto *)dato); }

int main() {
  GList lista = glist_crear();

  Contacto *c1 = contacto_crear("Pepe Argento", "3412695452", 61);
  lista = glist_agregar_inicio(lista, c1, f_copia_contacto);
  contacto_destruir(c1);

  Contacto *c2 = contacto_crear("Moni Argento", "3412684759", 60);
  lista = glist_agregar_inicio(lista, c2, f_copia_contacto);
  contacto_destruir(c2);

  Contacto *c3 = contacto_crear("Coqui Argento", "3415694286", 32);
  lista = glist_agregar_inicio(lista, c3, f_copia_contacto);
  contacto_destruir(c3);

  Contacto *c4 = contacto_crear("Paola Argento", "3416259862", 29);
  lista = glist_agregar_inicio(lista, c4, f_copia_contacto);
  contacto_destruir(c4);

  Contacto *c5 = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  lista = glist_agregar_inicio(lista, c5, f_copia_contacto);
  contacto_destruir(c5);

  Contacto *c6 = contacto_crear("Dardo Fuseneco", "3416894526", 64);
  lista = glist_agregar_inicio(lista, c6, f_copia_contacto);
  contacto_destruir(c6);

  printf("Lista original:\n");
  glist_recorrer(lista, f_imprimir_contacto);

  GList mayores = glist_filtrar(lista, es_mayor_de, f_copia_contacto);
  GList mayores2 = glist_filtrarR(lista, es_mayor_de, f_copia_contacto);
  GList mayores3 = glist_filtrarR2(lista, es_mayor_de, f_copia_contacto);

  printf("Mayores de 60:\n");
  glist_recorrer(mayores, f_imprimir_contacto);
  printf("Mayores de 60 R:\n");
  glist_recorrer(mayores2, f_imprimir_contacto);
  printf("Mayores de 60 R2:\n");
  glist_recorrer(mayores3, f_imprimir_contacto);

  glist_destruir(lista, f_dest_contacto);
  glist_destruir(mayores, f_dest_contacto);
  glist_destruir(mayores2, f_dest_contacto);
  glist_destruir(mayores3, f_dest_contacto);

  return 0;
}