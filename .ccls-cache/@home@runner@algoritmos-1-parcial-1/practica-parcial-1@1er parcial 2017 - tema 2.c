#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *pais;
  char *ciudad;
  int cantidadHabitantes;
  int importancia;
} Objetivo;

typedef struct nodo {
  Objetivo dato;
  struct nodo *anterior;
  struct nodo *siguiente;
} Nodo;

char *get_new_line() {
  char *line = malloc(sizeof(char) * 100);
  fgets(line, 100, stdin);
  int largo = strlen(line);

  while (line[largo - 1] != '\n') {
    line = realloc(line, sizeof(char) * (largo + 100));
    fgets(line + largo, 100, stdin);
    largo += strlen(line + largo);
  }

  line[largo - 1] = '\0';
  line = realloc(line, sizeof(char) * largo);
  return line;
}

Nodo *agregaObjetivo(Nodo *inicio, Objetivo o) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = o;
  nuevoNodo->siguiente = inicio;
  if (inicio->anterior != NULL) {
    nuevoNodo->anterior = inicio->anterior;
    inicio->anterior->siguiente = nuevoNodo;
    inicio->anterior = nuevoNodo;
  } else {
    nuevoNodo->anterior = inicio;
    inicio->siguiente = nuevoNodo;
    inicio->anterior = nuevoNodo;
  }
  return inicio;
}

void muestraCantidadHabitantesPorPais(Nodo *inicio, char *pais) {
  Nodo *temp = inicio;
  int contador = 0;
  char *paisI = inicio->dato.pais;
  char *ciudadI = inicio->dato.ciudad;
  if (inicio->siguiente != NULL) {
    for (; !(temp->siguiente->dato.pais == paisI &&
             temp->siguiente->dato.ciudad == ciudadI);
         temp = temp->siguiente) {
      if (temp->dato.pais == pais) {
        contador += temp->dato.cantidadHabitantes;
      }
    }
  } else if (inicio->dato.pais == pais) {
    contador += inicio->dato.cantidadHabitantes;
  }
  if (contador == 0) {
    printf("No hay objetivos para el pais solicitado \n");
  } else {
    printf("Se han encontrado %d objetivos para el pais %s", contador, pais);
  }

  // No compruebo si el pais ingresado existe o no
  // faltan los comentarios de el diseno de datos, signatura y declaracion,
  // ejemplos
}

Nodo *crear_lista() {
  Nodo *inicio = malloc(sizeof(Nodo));
  printf("Ingrese un pais: ");
  inicio->dato.pais = get_new_line();
  printf("Ingrese una ciudad: ");
  inicio->dato.ciudad = get_new_line();
  printf("Ingrese la cantidad de habitantes: ");
  scanf("%d", &(inicio->dato.cantidadHabitantes));
  int temp = 7;
  while (temp > 5 || temp < 1) {
    printf("Ingrese la importancia del objetivo con un numero del 1 al 5: ");
    scanf("%d%*c", &temp);
  }
  inicio->dato.importancia = temp;
  inicio->siguiente = NULL;
  inicio->anterior = NULL;
  return inicio;
}

void actualizar_objetivo(Objetivo *nObjetivo) {
  printf("Ingrese un pais: ");
  nObjetivo->pais = get_new_line();
  printf("Ingrese una ciudad: ");
  nObjetivo->ciudad = get_new_line();
  printf("Ingrese la cantidad de habitantes: ");
  scanf("%d%*c", &(nObjetivo->cantidadHabitantes));
  int temp = 7;
  while (temp > 5 || temp < 1) {
    printf("Ingrese la importancia del objetivo con un numero del 1 al 5: ");
    scanf("%d%*c", &temp);
  }
  nObjetivo->importancia = temp;
}

int main() {

  Nodo *dLista = crear_lista();
  int seguir = 0;
  printf("Quiere seguir agregando objetivos? (1 para si, 0 para no): ");
  scanf("%d%*c", &seguir);
  while (seguir) {
    Objetivo *nuevoObjetivo = malloc(sizeof(Objetivo));
    actualizar_objetivo(nuevoObjetivo);
    agregaObjetivo(dLista, *nuevoObjetivo);
    printf("Seguir agregando objetivos? (1 para si, 0 para no): ");
    scanf("%d%*c", &seguir);
  }

  printf("Ingrese un pais: ");
  char *paisObjetivo = get_new_line();
  muestraCantidadHabitantesPorPais(dLista, paisObjetivo);

  return 0;
}