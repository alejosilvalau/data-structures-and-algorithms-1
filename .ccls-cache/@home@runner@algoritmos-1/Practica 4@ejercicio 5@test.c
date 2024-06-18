#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

void visit_buscar(int dato, Contenedor *c) {
  printf("dato: %d y c dato: %d\n", dato, c->datoBuscado);
  if (dato == c->datoBuscado && c->encontrado == 0)
    c->encontrado = 1;
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
  printf("jaja nodos = %d\n", nodos);
  
  // b
  
  int se_encuentra = btree_buscar(raiz, 4);
  printf("se encuentra; %d\n", se_encuentra);
  
  se_encuentra = btree_buscar(raiz, 5);
  printf("se encuentra; %d\n", se_encuentra);
  
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
  
  // 4
  // a
  Contenedor con;
  con.datoBuscado = 3;
  con.encontrado = 0;
  btree_recorrer_extra(raiz, BTREE_RECORRIDO_IN, (FuncionVisitanteExtra)visit_buscar, &con);
  printf("nodos que tienen un 3: %d\n", con.encontrado);
  
  //5
  puts("");
  printf("FUNCION BFS\n");
  btree_recorrer_bfs(raiz, imprimir_entero, 0);
  puts("");
  
  btree_destruir(raiz);
  return 0;
}
