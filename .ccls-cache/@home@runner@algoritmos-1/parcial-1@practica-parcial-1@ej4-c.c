#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *direccion;
  int capacidad;
} ArregloEnteros;

void arreglo_enteros_eliminar(ArregloEnteros *arreglo, int pos) {
  if (pos < 1 || pos > arreglo->capacidad) {
    printf("Error: Posición inválida.\n");
    return;
  }

  // Mueve los elementos posteriores un lugar a la izquierda
  for (int i = pos - 1; i < arreglo->capacidad - 1; i++) {
    arreglo->direccion[i] = arreglo->direccion[i + 1];
  }

  // Reduzca el tamaño del arreglo
  int nuevaCapacidad = arreglo->capacidad - 1;
  arreglo->direccion =
      realloc(arreglo->direccion, sizeof(int) * nuevaCapacidad);
  arreglo->capacidad = nuevaCapacidad;
}

int main() {
  // Ejemplo de uso
  ArregloEnteros miArreglo;
  miArreglo.capacidad = 5;
  miArreglo.direccion = (int *)malloc(sizeof(int) * miArreglo.capacidad);

  for (int i = 0; i < miArreglo.capacidad; i++) {
    miArreglo.direccion[i] = i + 1;
  }

  printf("Arreglo antes de eliminar el elemento \n");
  for (int i = 0; i < miArreglo.capacidad; i++) {
    printf("%d ", miArreglo.direccion[i]);
  }
  printf("\n");

  int posicionAEliminar = 3;
  arreglo_enteros_eliminar(&miArreglo, posicionAEliminar);

  printf("Arreglo después de eliminar el elemento en la posición %d:\n",
         posicionAEliminar);
  for (int i = 0; i < miArreglo.capacidad; i++) {
    printf("%d ", miArreglo.direccion[i]);
  }
  printf("\n");

  free(miArreglo.direccion);
  return 0;
}
