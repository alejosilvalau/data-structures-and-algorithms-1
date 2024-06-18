#include "btree.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -Wall main.c cola.c glist.c btree.c -g -o main
// ./main

typedef struct {
  Cola q1;
  Cola q2;
} XStack;

typedef struct {
  char *nombre;
  char *telefono;
  unsigned int edad;
} Contacto;

// ya estan hechas las implementaciones de "xstack_top" y "xstack_destroy"
// se tienen que usar dos colas para implementar la pila

// xstack_create

XStack *stack_create() {
  XStack *stack = malloc(sizeof(XStack));
  stack->q1 = cola_crear();
  stack->q2 = cola_crear();
  return stack;
}

// o si "queue_create() no esta definido:

// XQueue *queue_create() {
//   XQueue *q = malloc(sizeof(XQueue));
//   q->first = NULL;
//   q->last = NULL;
//   return q;
// }

// xstack_push

void *copiaContacto(void *data) {
  Contacto *contacto = (Contacto *)data;
  Contacto *nuevo = malloc(sizeof(Contacto));

  nuevo->nombre = malloc(sizeof(char) * (strlen(contacto->nombre) + 1));
  strcpy(nuevo->nombre, contacto->nombre);
  nuevo->telefono = malloc(sizeof(char) * (strlen(contacto->telefono) + 1));
  strcpy(nuevo->telefono, contacto->telefono);
  nuevo->edad = contacto->edad;

  return nuevo;
}

void imprimirContacto(void *data) {
  Contacto *contacto = (Contacto *)data;
  printf("Nombre: %s - Telefono: %s - Edad: %d\n", contacto->nombre,
         contacto->telefono, contacto->edad);
}

void destruirContacto(void *data) {
  Contacto *contacto = (Contacto *)data;

  free(contacto->nombre);
  free(contacto->telefono);
  free(contacto);
}

void NoDestruirContacto(void *data) { return; }
void *NoCopiaContacto(void *data) { return data; }

XStack *stack_push(XStack *stack, void *data) {
  if (cola_es_vacia(stack->q1)) {
    cola_encolar(stack->q1, data, copiaContacto);

    while (!cola_es_vacia(stack->q2)) {
      Contacto *contacto = (Contacto *)cola_inicio(stack->q2);
      stack->q2 = cola_desencolar(stack->q2, NoDestruirContacto);
      cola_encolar(stack->q1, contacto, NoCopiaContacto);
    }
    return stack;
  }
  cola_encolar(stack->q2, data, copiaContacto);

  while (!cola_es_vacia(stack->q1)) {
    Contacto *contacto = (Contacto *)cola_inicio(stack->q1);
    stack->q1 = cola_desencolar(stack->q1, NoDestruirContacto);
    cola_encolar(stack->q2, contacto, NoCopiaContacto);
  }
  return stack;
}

// xstack_pop

void *stack_pop(XStack *stack) {
  if (!(cola_es_vacia(stack->q1))) {
    Contacto *contacto = (Contacto *)cola_inicio(stack->q1);
    stack->q1 = cola_desencolar(stack->q1, NoDestruirContacto);
    return (void *)contacto;
  }

  Contacto *contacto = (Contacto *)cola_inicio(stack->q2);
  stack->q2 = cola_desencolar(stack->q2, NoDestruirContacto);
  return (void *)contacto;
}

// xstack_is_empty

int xstack_is_empty(XStack *stack) {
  return cola_es_vacia(stack->q1) && cola_es_vacia(stack->q2);
}

// extra

void xstack_destroy(XStack *stack) {
  cola_destruir(stack->q1, destruirContacto);
  cola_destruir(stack->q2, destruirContacto);
  free(stack);
}


void imprime_compara(int dato, int *extra) {
  printf("Dato: %d\n", dato);
  if (dato > *extra) {
    *extra = dato;
  }
}


int main() {
  XStack *pila = stack_create();

  Contacto *contacto = malloc(sizeof(Contacto));
  contacto->nombre = malloc(sizeof(char) * 100);
  contacto->telefono = malloc(sizeof(char) * 100);

  strcpy(contacto->nombre, "Bautista");
  strcpy(contacto->telefono, "34356535");
  contacto->edad = 22;
  stack_push(pila, contacto);

  strcpy(contacto->nombre, "Sebastian");
  strcpy(contacto->telefono, "34254535");
  contacto->edad = 23;
  stack_push(pila, contacto);

  strcpy(contacto->nombre, "Federico");
  strcpy(contacto->telefono, "34298735");
  contacto->edad = 48;
  stack_push(pila, contacto);

  strcpy(contacto->nombre, "Valentina");
  strcpy(contacto->telefono, "34254334");
  contacto->edad = 25;
  stack_push(pila, contacto);

  destruirContacto(contacto);
  printf("Pila es vacia?: %d\n", xstack_is_empty(pila));

  printf("Pila:\n");
  while (!xstack_is_empty(pila)) {
    Contacto *contacto = (Contacto *)stack_pop(pila);
    imprimirContacto(contacto);
    destruirContacto(contacto);
  }
  printf("Pila es vacia?: %d\n", xstack_is_empty(pila));
  xstack_destroy(pila);


  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  puts("");
  printf("Arbol:\n");
  int minDato = 0;
  printf("Maximo pre arbol: %d\n", minDato);
  btree_foreach(raiz, (FuncionVisitanteExtra) imprime_compara, &minDato);
  puts("");
  printf("Maximo post arbol: %d\n", minDato);
  puts("");
  btree_destruir(raiz);
  return 0;
}

// static void *copiar_puntero_entero(void *i) {
//   int *p = malloc(sizeof(int));
//   *p = *(int *)i;
//   return (void *)p;
// }