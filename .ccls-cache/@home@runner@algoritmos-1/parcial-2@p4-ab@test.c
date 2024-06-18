// gcc -Wall test.c btree.c pila.c arregloenteros.c -g -o main
// valgrind ./main

#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimir_entero(int data) { printf("%d ", data); }

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree lr = btree_unir(5, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, lr);
  BTree rl = btree_unir(15, btree_crear(), btree_crear());
  BTree rr = btree_unir(65, btree_crear(), btree_crear());
  BTree r = btree_unir(3, rl, rr);
  BTree raiz = btree_unir(4, l, r);

  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");

  puts("");
  printf("La cantidad de nodos del arbol es: %d\n", btree_nnodos(raiz));
  puts("");

  int valor = 1;
  printf("Esta %d en el arbol? %d \n", valor, btree_buscar(raiz, valor));
  valor = 45;
  printf("Esta %d en el arbol? %d \n", valor, btree_buscar(raiz, valor));
  puts("");

  printf("Arbol original:\n");
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");
  printf("Arbol copia:\n");
  BTree raiz2 = btree_crear();
  raiz2 = btree_copiar(raiz);
  btree_recorrer(raiz, BTREE_RECORRIDO_IN, imprimir_entero);
  puts("");

  puts("");
  printf("La altura del arbol es: %d\n", btree_altura(raiz));
  puts("");
  int pro = 1;
  printf("La cantidad de nodos de profundidad %d es: %d\n", pro,
         btree_nnodos_profundidad(raiz, pro));

  puts("");
  int dato = 3;
  printf("La profundidad del valor %d es: %d\n", dato,
         btree_profundidad(raiz, dato));
  puts("");
  printf("La suma total de los datos del arbol es: %d\n", btree_sumar(raiz));

  // puts("");
  // printf("Los nodos de profundidad %d son:\n", pro);
  // btree_recorrer_bfs(raiz, imprimir_entero, pro);
  // puts("");

  btree_destruir(raiz2);
  btree_destruir(raiz);

  return 0;
}
