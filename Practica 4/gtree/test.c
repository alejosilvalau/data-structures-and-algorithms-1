#include "gtree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Casos de prueba para arboles generales
 */

/**
 * Funciones para usar arboles generales con datos de tipo int *
 */
static void *copiar_puntero_entero(void *i) {
  int *p = malloc(sizeof(int));
  *p = *(int *)i;
  return p;
}
static int comparar_puntero_entero(void *i1, void *i2) {
  return (*(int *)i1 - *(int *)i2);
}
static void destruir_puntero_entero(void *i) { free(i); }
static void imprimir_puntero_entero(void *i,
                                    __attribute__((unused)) void *extra) {
  printf("%d ", *(int *)i);
}

int main() {

  /** Construimos el siguiente arbol:
   *     1
   *  /  |  \
   * 2   3   4
   *    / \   \
   *   5   6   7
   *         / | \
   *        8  9  10
   */
  int datos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTree tree = gtree_crear();
  tree = gtree_agregar(tree, NULL, datos, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos, datos + 3, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos, datos + 2, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos, datos + 1, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 2, datos + 5, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 2, datos + 4, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 3, datos + 6, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 6, datos + 9, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 6, datos + 8, copiar_puntero_entero,
                       comparar_puntero_entero);
  tree = gtree_agregar(tree, datos + 6, datos + 7, copiar_puntero_entero,
                       comparar_puntero_entero);
  puts("El arbol es:");
  gtree_recorrer_extra(tree, imprimir_puntero_entero, NULL);
  puts("");
  printf("El arbol tiene %d nodos\n", gtree_nnodos(tree));
  gtree_destruir(tree, destruir_puntero_entero);
  return 0;
}