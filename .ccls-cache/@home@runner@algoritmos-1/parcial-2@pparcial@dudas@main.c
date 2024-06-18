#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap2.h"

// gcc -Wall main.c heap2.c -g -o main
// ./main

typedef struct _AVL_Nodo {
  int dato;
  struct _AVL_Nodo *izq, *der;
  int altura;
} AVL_Nodo;

typedef AVL_Nodo* AVL;

#define ARBOL (AVL)1)


void heapify(Heap heap, int largo) {
  if (heap->cantidad <= 1) return;

  for (int i = 1; i < largo; i++) {
    int pos_padre = padre(heap->data[i]);
    if (heap->data[i] > heap->data[pos_padre]) {
      flotar(heap->data, i, largo);
    } else {
      hundir(heap->data, i, largo);
    }
  }
}

int main () {

  // AVL nodo = malloc(sizeof(AVL_Nodo));
  // nodo->izq = NULL;
  // nodo->der = NULL;
 
  // if (/* What do I put here? */) {
  //   printf("Hola");
  // }

  // free(nodo);

  int arr[] = {1, 12, 9, 5, 6, 10};
  int n = 6;
  
  Heap heap = malloc(sizeof(struct _Heap));
  heap->data = malloc(sizeof(int) * n);
  
  for (int i = 0; i < n; i++) {
    heap_insertar(heap, arr[i]);
  }
  puts("");
  
  for (int i = 0; i < n; i++) {
    printf("%d ", heap->data[i]);
  }
  puts("");
  
  heapify(heap, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", heap->data[i]);
  }
  puts("");
  
  return 0;
}

// Los arboles 2-3, se comprobaban si habia un solo elemento con la constante dada.
// No me acuerdo como era, pero en vez de comprobar con NULL en int, se comprueba con la
// Constante.