#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// gcc -Wall heap.c test.c -g -o main
// ./main

static void *copiar_puntero_entero(void *i) {
  int *p = malloc(sizeof(int));
  *p = *(int *)i;
  return (void *)p;
}

static int comparar_puntero_entero(void *i1, void *i2) {
  return (*(int *)i1 - *(int *)i2);
}

static void destruir_puntero_entero(void *i) { free(i); }

static void imprimir_puntero_entero(void *i) { printf("%d ", *(int *)i); }

int main() {

  BHeap heap = bheap_crear(10, comparar_puntero_entero);

  for (int i = 1; i < 10; i++) {
    int random = rand() % 100;
    heap = bheap_insertar(heap, &random, copiar_puntero_entero);
    assert(bheap_es_vacio(heap) == 0);
  }
  printf("Current Heap: ");
  bheap_recorrer(heap, imprimir_puntero_entero);
  puts("");

  int *max = bheap_eliminar(heap);
  printf("Anterior raiz: %d\n", *max);
  printf("Nuevo heap: ");
  bheap_recorrer(heap, imprimir_puntero_entero);
  puts("");
  puts("");

  bheap_destruir(heap, destruir_puntero_entero);

  BHeap heap2 = bheap_crear(6, comparar_puntero_entero);

  int numero = 10;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);
  numero = 8;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);
  numero = 11;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);
  numero = 9;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);
  numero = 12;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);
  numero = 2;
  heap2 = bheap_insertar(heap2, &numero, copiar_puntero_entero);

  printf("Heap ejercicio parcial: ");
  bheap_recorrer(heap, imprimir_puntero_entero);
  puts("");

  max = bheap_eliminar(heap);
  printf("Anterior raiz: %d\n", *max);
  printf("Heap despues de eliminaciones: ");
  bheap_recorrer(heap, imprimir_puntero_entero);
  puts("");
  max = bheap_eliminar(heap);
  printf("Anterior raiz 2: %d\n", *max);

  printf("Heap despues de eliminaciones: ");
  bheap_recorrer(heap, imprimir_puntero_entero);
  puts("");

  bheap_destruir(heap, destruir_puntero_entero);
  
  puts("Ok");
  return 0;
}

/*
------------------ PRUEBA SWAP ------------------
int *i_ptr = malloc(sizeof(int));
*i_ptr = 0;

int *j_ptr = malloc(sizeof(int));
*j_ptr = 1;

printf("i: %d, j: %d\n", *i_ptr, *j_ptr);

swap((void*)i_ptr, (void*)j_ptr);
printf("i: %d, j: %d\n", *i_ptr, *j_ptr);
--------------------------------------------------
*/