#include "tablahash.h"
#include "usuario.h"
#include <stdio.h>

// gcc -Wall main.c tablahash.c usuario.c -o main
// ./main

#define TABLA_CAPACIDAD 10

// typedef struct {
//   Usuario *inicio;
//   Usuario *final;
// } Cola;

// El operador ingresa un usuario por teclado
// El sistema busca el usuario dado, si esta lo devuelve
// En caso que no este, lo crea y lo devuelve

int main() {
  TablaHash *tabla = tablahash_crear(
      TABLA_CAPACIDAD, (FuncionHashear)usuario_hashear,
      (FunctionCopiar)usuario_copiar, (FunctionComparar)usuario_comparar);

  Usuario *usuarios[7];
  usuarios[0] = usuario_crear("32444234", 0);
  usuarios[1] = usuario_crear("32444323", 0);
  usuarios[2] = usuario_crear("43144234", 0);
  usuarios[3] = usuario_crear("55344231", 0);
  usuarios[4] = usuario_crear("55344231", 0);
  usuarios[5] = usuario_crear("65744255", 0);
  usuarios[6] = usuario_crear("65767676", 0);
  
  printf("Insercion:\n");
  for (int i = 0; i < 6; i++)
    tablahash_insertar(tabla, usuarios[i]);
  puts("");
  
  printf("Busqueda:\n");
  for (int i = 0; i < 7; i++)
    if (tablahash_buscar(tabla, usuarios[i]))
      printf("El usuario %s esta en la tabla\n", usuarios[i]->dni);
    else
      printf("El usuario no esta en la tabla\n");

  return 0;
}