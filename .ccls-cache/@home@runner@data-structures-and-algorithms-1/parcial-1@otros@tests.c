#include "stdio.h"
#include "stdlib.h"

int main() {
  int valor, cantidad = 0;
  int *numeros = NULL;

  do {
    printf("Ingrese un valor entero (0 para finalizar): ");
    scanf("%d", &valor);
    cantidad++;

    numeros = realloc(numeros, cantidad * sizeof(int));
    numeros[cantidad - 1] = valor;
  } while (valor != 0);

  printf("Numeros ingresados: ");
  for (int n = 0; n < cantidad - 1; n++)
    printf("%d", numeros[n]);
  free(numeros);
  return 0;
}
