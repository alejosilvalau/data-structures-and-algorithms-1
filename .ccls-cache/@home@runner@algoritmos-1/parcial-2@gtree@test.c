// gcc -Wall test.c gtree.c -g -o main
// valgrind ./main

#include "gtree.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(void *data) { printf("%d ", *(int *)data); }

int main() {

  void *n1 = malloc(sizeof(int));
  *((int *)n1) = 15;

  void *n2 = malloc(sizeof(int));
  *((int *)n2) = 42;

  void *n3 = malloc(sizeof(int));
  *((int *)n3) = 543;

  void *n4 = malloc(sizeof(int));
  *((int *)n4) = 433;

  BTree ll = btree_unir(n1, btree_crear(), btree_crear());
  BTree l = btree_unir(n2, ll, btree_crear());
  BTree r = btree_unir(n3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(n4, l, r);

  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  free(n1);
  free(n2);
  free(n3);
  free(n4);
  btree_destruir(raiz);

  return 0;
}
