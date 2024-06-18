#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  printf("Altura: %d\n", btree_altura(raiz));

  printf("Suma: %d\n", btree_sumar(raiz));
  printf("Suma extra: %d\n", btree_sumar_extra(raiz));

  printf("Cant. de nodos: %d\n", btree_nnodos(raiz));
  printf("Cant. de nodos extra: %d\n", btree_nnodos_extra(raiz));

  printf("Busqueda de 4: %d, Busqueda de 5: %d\n",
    btree_buscar(raiz, 4), btree_buscar(raiz, 5));
  printf("Busqueda extra de 4: %d, Busqueda extra de 5: %d\n",
    btree_buscar_extra(raiz, 4), btree_buscar_extra(raiz, 5));

  printf("Profunidad de 1, 4, y -5: %d, %d, %d\n", btree_profundidad(raiz, 1),
  btree_profundidad(raiz, 4), btree_profundidad(raiz, -5));

  printf("Nodos prof. 1, 2 y 3: %d, %d, %d\n", btree_nnodos_profundidad(raiz, 1),
          btree_nnodos_profundidad(raiz, 2), btree_nnodos_profundidad(raiz, 3));

  btree_destruir(raiz);

  return 0;
}
