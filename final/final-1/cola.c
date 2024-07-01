#include "cola.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Cola *cola_crear(FuncionComparar comparar, FuncionComparar comparar_aux,
                 FuncionCopiar copiar, FuncionDestruir destruir,
                 FuncionVisitar visitar) {
  Cola *nuevaCola = malloc(sizeof(Cola));
  assert(nuevaCola != NULL);
  nuevaCola->inicio = NULL;
  nuevaCola->final = NULL;

  nuevaCola->comparar = comparar;
  nuevaCola->comparar_aux = comparar_aux;
  nuevaCola->copiar = copiar;
  nuevaCola->destruir = destruir;
  nuevaCola->visitar = visitar;

  return nuevaCola;
}

int cola_vacia(Cola *cola) { return (cola->inicio == NULL); }

Cola *cola_encolar(Cola *cola, void *dato) {
  CNodo *nuevoNodo = malloc(sizeof(CNodo));
  nuevoNodo->sig = NULL;
  nuevoNodo->dato = cola->copiar(dato);

  if (cola_vacia(cola)) {
    cola->inicio = nuevoNodo;
    cola->final = nuevoNodo;
    return cola;
  }

  // Comprobamos con el primer nodo
  if (cola->comparar_aux(nuevoNodo->dato, cola->inicio->dato) > 0 &&
      cola->comparar(dato, cola->inicio->dato) != 0) {
    nuevoNodo->sig = cola->inicio;
    cola->inicio = nuevoNodo;
    return cola;
  }

  // comparar en los nodos de la cola, para ver donde agregarlo
  for (CNodo *temp = cola->inicio; temp->sig != NULL; temp = temp->sig) {
    if (cola->comparar(dato, temp->dato) == 0) {
      return cola;
    }
    if (cola->comparar_aux(dato, temp->sig->dato) > 0) {
      nuevoNodo->sig = temp->sig;
      temp->sig = nuevoNodo;
      return cola;
    }
  }
  // agregar el nodo al final
  cola->final->sig = nuevoNodo;
  cola->final = nuevoNodo;
  return cola;
}

void cola_proximo(Cola *cola) { cola->visitar(cola->inicio->dato); }

void cola_imprimir(Cola *cola) {
  for (CNodo *temp = cola->inicio; temp != NULL; temp = temp->sig)
    cola->visitar(temp->dato);
}

Cola *cola_desencolar(Cola *cola, void *dato) {
  if (cola_vacia(cola))
    return cola;

  // Si no se paso ningun dato, o el dato que se quiere eliminar es
  // el primero, se elimina el primer nodo.
  if (dato == NULL || cola->comparar(dato, cola->inicio->dato) == 0) {
    CNodo *aux = cola->inicio;
    cola->inicio = cola->inicio->sig;
    cola->destruir(aux->dato);
    free(aux);
    return cola;
  }

  // comparar en los nodos de la cola, para ver si el dato esta en la cola.
  // En el caso que este, eliminarlo
  for (CNodo *temp = cola->inicio; temp->sig != NULL; temp = temp->sig) {
    if (cola->comparar(dato, temp->sig->dato) == 0) {
      CNodo *aux = temp->sig;
      temp->sig = aux->sig;
      if (aux->dato == cola->final)
        cola->final = temp->sig;
      cola->destruir(aux->dato);
      free(aux);
      return cola;
    }
  }

  // El dato no esta en la cola, no se elimina nada
  return cola;
}