#include "arregloenteros.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -Wall main.c cola.c glist.c pila.c arregloenteros.c -g -o main
// ./main

typedef struct {
  char *nombre;
  char *telefono;
  int edad;
} Contacto;

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

// int main() {
//   Cola cola = cola_crear();

//   Contacto *contacto = malloc(sizeof(Contacto));
//   contacto->nombre = malloc(sizeof(char) * 100);
//   contacto->telefono = malloc(sizeof(char) * 100);

//   strcpy(contacto->nombre, "Bautista");
//   strcpy(contacto->telefono, "34356535");
//   contacto->edad = 22;
//   cola_encolar(cola, contacto, copiaContacto);

//   strcpy(contacto->nombre, "Sebastian");
//   strcpy(contacto->telefono, "34254535");
//   contacto->edad = 23;
//   cola_encolar(cola, contacto, copiaContacto);

//   strcpy(contacto->nombre, "Federico");
//   strcpy(contacto->telefono, "34298735");
//   contacto->edad = 48;
//   cola_encolar(cola, contacto, copiaContacto);

//   strcpy(contacto->nombre, "Valentina");
//   strcpy(contacto->telefono, "34254334");
//   contacto->edad = 25;
//   cola_encolar(cola, contacto, copiaContacto);

//   printf("Cola Original: \n");
//   cola_imprimir(cola, imprimirContacto);

//   printf("\nCola vacia?:\n");
//   printf("%d\n", cola_es_vacia(cola));

//   printf("\nPrimer valor:\n");
//   imprimirContacto(cola_inicio(cola));

//   printf("\nCola Original: \n");
//   cola_imprimir(cola, imprimirContacto);

//   printf("\nDesencolar:\n");
//   cola = cola_desencolar(cola, destruirContacto);
//   cola_imprimir(cola, imprimirContacto);

//   cola_destruir(cola, destruirContacto);

//   return 0;
// }

int main() {
  // ArregloEnteros *arreglo = arreglo_enteros_crear(10);
  // arreglo_enteros_imprimir(arreglo);
  // arreglo_enteros_destruir(arreglo);
  // return 0;

  int cero;
  printf("%d\n", cero);
}