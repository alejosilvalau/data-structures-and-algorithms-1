#include "cola.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

// gcc -Wall main-cola.c glist.c -g -o main
// ./main

Cola cola_crear() {
  Cola cola = malloc(sizeof(struct _GList));
  cola->first = NULL;
  cola->last = NULL;
  return cola;
}

void cola_destruir(Cola cola, FuncionDestructora destroy) {
  glist_destruir_node(cola->first, destroy);
  free(cola);
}



int main() {
  printf("hello world\n");

  return 0;
}