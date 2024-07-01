#include "usuario.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
* Funcion hash para strings
*/
static unsigned KRHash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}

Usuario *usuario_crear(char *dni, int tiempo) {
  Usuario *nuevo = malloc(sizeof(Usuario));
  assert(nuevo != NULL);

  nuevo->dni = malloc(sizeof(char) * (strlen(dni) + 1));
  assert(nuevo->dni != NULL);
  strcpy(nuevo->dni, dni);

  nuevo->tiempo = tiempo;

  return nuevo;
}

int usuario_comparar(Usuario *u1, Usuario *u2) {
  return strcmp(u1->dni, u2->dni);
}

Usuario *usuario_copiar(Usuario *u) {
  Usuario *copia = usuario_crear(u->dni, u->tiempo);
  return copia;
}

unsigned usuario_hashear(Usuario *u) { return KRHash(u->dni); }