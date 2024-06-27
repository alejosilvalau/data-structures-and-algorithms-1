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

  // ejercicio 2
  btree_recorrer(raiz, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  
  // ejercicio 3
  int nodos = btree_nnodos(raiz);
  printf("nodos del arbol: %d\n", nodos);
  
  // b
  
  int se_encuentra = btree_buscar(raiz, 4);
  printf("el entero 4 se encuentra; %d\n", se_encuentra);
  
  se_encuentra = btree_buscar(raiz, 5);
  printf("el entero 5 se encuentra; %d\n", se_encuentra);
  
  // c
  
  BTree copia = btree_copiar(raiz);
  printf("copia:\n");
  btree_recorrer(copia, BTREE_RECORRIDO_POST, imprimir_entero);
  puts("");
  
  // d
  int altura = btree_altura(raiz);
  printf("altura: %d\n", altura);
  
  // e
  int nodos_profundidad = btree_nnodos_profundidad(raiz, 1);
  printf("nodos en esta profundidad: %d\n", nodos_profundidad);
  
  
  // f
  int prof = btree_profundidad(raiz, 4, 0);
  printf("profundidad del dato dado: %d\n", prof);
  
  // g
  int suma = btree_sumar(raiz);
  printf("la suma de sus nodos es: %d\n", suma);
  
  btree_destruir(raiz);
  return 0;
}
