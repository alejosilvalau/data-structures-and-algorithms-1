#include <stdio.h>
#include <stdlib.h>

// cd practica
// gcc -Wall 1er-parcial-1023.c -g -o main
// ./main

typedef struct _SONodo {
  int dato;
  struct _SONodo *sig;
} SOList;

SOList *solist_add(int dato, SOList *oLista) {
  SOList *nuevoNodo = malloc(sizeof(SOList));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (oLista == NULL)
    return nuevoNodo;

  if (oLista->dato > dato) {
    nuevoNodo->sig = oLista;
    return nuevoNodo;
  }

  SOList *temp = oLista;
  for (; temp->sig != NULL && temp->sig->dato < dato; temp = temp->sig)
    ;
  nuevoNodo->sig = temp->sig;
  temp->sig = nuevoNodo;

  return oLista;
}

void solist_destroy(SOList *oLista) {
  SOList *nodoAEliminar;
  while (oLista != NULL) {
    nodoAEliminar = oLista;
    oLista = oLista->sig;
    free(nodoAEliminar);
  }
}

void solist_print(SOList *oLista) {
  for (SOList *nodo = oLista; nodo != NULL; nodo = nodo->sig)
    printf("%d \n", nodo->dato);
}

void print_ordered(int arreglo[], int longitud) {
  SOList *sOArreglo = NULL;
  for (int i = 0; i < longitud; i++) {
    sOArreglo = solist_add(arreglo[i], sOArreglo);
  }

  solist_print(sOArreglo);
  solist_destroy(sOArreglo);
}

int main() {
  SOList *lista = NULL;
  lista = solist_add(45, lista);
  lista = solist_add(3, lista);
  lista = solist_add(-1, lista);

  solist_print(lista);
  solist_destroy(lista);

  SOList *lista2 = NULL;
  lista2 = solist_add(5, lista2);
  lista2 = solist_add(2, lista2);
  lista2 = solist_add(3, lista2);
  lista2 = solist_add(2, lista2);

  solist_print(lista2);
  solist_destroy(lista2);

  int array[] = {1, 4, 5, 2, 5, 6};
  print_ordered(array, 6);

  return 0;
}