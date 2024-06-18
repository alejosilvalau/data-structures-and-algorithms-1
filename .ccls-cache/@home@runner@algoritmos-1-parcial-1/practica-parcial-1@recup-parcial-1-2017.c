#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *dni, *nombre, *descripcionCargo;
  int prioridad;
} _Invitado;
typedef _Invitado *Invitado;

typedef struct _Nodo {
  Invitado invitado;
  struct _Nodo *sig, *ant;
} Nodo;
typedef Nodo *Lista;

Lista agregar(Invitado invitado, Lista listaDeInvitados) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->invitado = invitado;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = NULL;

  if (listaDeInvitados == NULL)
    return nuevoNodo;

  else {
    Nodo *temp = listaDeInvitados;
    for (; temp->sig != NULL &&
           temp->sig->invitado->prioridad < invitado->prioridad;
         temp = temp->sig)
      ;
    nuevoNodo->sig = temp->sig;
    nuevoNodo->ant = temp;
    if (temp->sig != NULL)
      temp->sig->ant = nuevoNodo;
    temp->sig = nuevoNodo;
  }
  return listaDeInvitados;
}
/*
void invitado_destruir(Invitado invitado) {
  free(invitado->dni);
  free(invitado->nombre);
  free(invitado->descripcionCargo);
  free(invitado);
}

*/

/*
Lista eliminar(Lista listaDeInvitados, int prioridadAprobada) {
  if (listaDeInvitados == NULL)
    return NULL;
  if (listaDeInvitados->invitado->prioridad == prioridadAprobada &&
      listaDeInvitados->sig == NULL) {
    invitado_destruir(listaDeInvitados->invitado);
    free(listaDeInvitados);
    return NULL;
  }
  Nodo *nodoEliminar, *inicio = listaDeInvitados;
  while (listaDeInvitados->sig != inicio &&
         listaDeInvitados->invitado->prioridad <= prioridadAprobada) {
    if (listaDeInvitados->invitado->prioridad < prioridadAprobada) {
      listaDeInvitados = listaDeInvitados->sig;
    } else {
      nodoEliminar = listaDeInvitados;
      listaDeInvitados = listaDeInvitados->sig;
      invitado_destruir(nodoEliminar->invitado);
      free(nodoEliminar);
    }
  }
  return listaDeInvitados->sig;
}

*/

Lista eliminar(Lista listaDeInvitados, int prioridadAprobada) {
  if (listaDeInvitados == NULL)
    return NULL;

  Nodo *temp = listaDeInvitados, *inicio = listaDeInvitados;
  while (temp != NULL) {
    if (temp->invitado->prioridad == prioridadAprobada) {
      if (temp->ant != NULL)
        temp->ant->sig = temp->sig;
      if (temp->sig != NULL)
        temp->sig->ant = temp->ant;

      Nodo *nextTemp = temp->sig;
      free(temp->invitado);
      free(temp);
      temp = nextTemp;
    } else {
      temp = temp->sig;
      if (temp->sig == inicio) {
        break;
      }
    }
  }

  return listaDeInvitados;
}

int main() {
  Invitado invitado1 = malloc(sizeof(_Invitado));
  invitado1->dni = "12345678A";
  invitado1->nombre = "Juan";
  invitado1->descripcionCargo = "Presidente";
  invitado1->prioridad = 1;

  Invitado invitado2 = malloc(sizeof(_Invitado));
  invitado2->dni = "23456789A";
  invitado2->nombre = "Maria";
  invitado2->descripcionCargo = "Vicepresidente";
  invitado2->prioridad = 2;

  Invitado invitado3 = malloc(sizeof(_Invitado));
  invitado3->dni = "23456789A";
  invitado3->nombre = "Hernesto";
  invitado3->descripcionCargo = "Vicepresidente";
  invitado3->prioridad = 1;

  Lista listaDeInvitados = agregar(invitado1, NULL);
  listaDeInvitados = agregar(invitado2, listaDeInvitados);
  listaDeInvitados = agregar(invitado3, listaDeInvitados);

  printf("Lista de invitados:\n");
  for (Nodo *temp = listaDeInvitados; temp != NULL; temp = temp->sig) {
    printf("Nombre: %s\n", temp->invitado->nombre);
  }

  listaDeInvitados = eliminar(listaDeInvitados, 1);

  printf("Lista de invitados:\n");
  // for (Nodo *temp = listaDeInvitados; temp != NULL && temp->sig != NULL;
  //      temp = temp->sig) {
  //   printf("Nombre: %s\n", temp->invitado->nombre);
  // }

  printf("Nombre: %s\n", listaDeInvitados->invitado->nombre);

  return 0;
}