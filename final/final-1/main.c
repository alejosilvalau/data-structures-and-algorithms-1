#include "cola.h"
#include "tablahash.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -Wall main.c tablahash.c usuario.c cola.c -o main
// ./main

#define TABLA_CAPACIDAD 10
#define LONGITUD_DNI 8

int main() {

  // Usuarios de la empresa
  Usuario *usuarios[7];
  usuarios[0] = usuario_crear("32444234", 0);
  usuarios[1] = usuario_crear("32444323", 1);
  usuarios[2] = usuario_crear("43144234", 10);
  usuarios[3] = usuario_crear("55344231", 3);
  usuarios[4] = usuario_crear("55344231", 3);
  usuarios[5] = usuario_crear("65744255", 4);

  TablaHash *tabla = tablahash_crear(
      TABLA_CAPACIDAD, (FuncionHashear)usuario_hashear,
      (FuncionCopiar)usuario_copiar, (FuncionComparar)usuario_comparar);

  for (int i = 0; i < 6; i++)
    tablahash_insertar(tabla, usuarios[i]);

  Cola *cola = cola_crear(
      (FuncionComparar)usuario_comparar,
      (FuncionComparar)usuario_comparar_tiempo, (FuncionCopiar)usuario_copiar,
      (FuncionDestruir)usuario_destruir, (FuncionVisitar)usuario_imprimir);

  while (1) {
    puts("---------------------");
    puts("");
    printf("Bienvenido al sistema de gestion de usuarios de espera:\n");
    puts("");
    printf("Que desea hacer?:\n");
    printf("  1 - Agregar un usuario en espera?\n");
    printf("  2 - Remover un usuario dado de la espera?\n");
    printf("  3 - Mostrar el proximo usuario a ser atendido segun la "
           "politica de "
           "la empresa?\n");
    puts("");
    int opcion = 0;
    while (1 > opcion || opcion > 3) {
      printf("Ingrese la opcion deseada: ");
      if (scanf("%d", &(opcion)))
        puts("");
    }
    puts("---------------------");
    puts("");

    if (opcion == 1) {
      // Creamos el usuario
      char *dni = malloc(sizeof(char) * (LONGITUD_DNI + 1));
      printf("Ingrese el dni del usuario: ");
      if (scanf("%s", dni))
        puts("");

      int tiempo;
      printf("Ingrese el tiempo que el usuario pago la membresia premium: ");
      if (scanf("%d", &(tiempo)))
        puts("");
      Usuario *usuario = usuario_crear(dni, tiempo);

      if (tablahash_buscar(tabla, usuario)) {
        cola = cola_encolar(cola, usuario);
        printf("Se agrego en espera el usuario ");
        usuario_imprimir(usuario);
      } else
        printf("  ¡El usuario no esta registrado en la empresa!\n");
      puts("");

    } else if (opcion == 2) {
      if (!cola_vacia(cola)) {
        int respuesta;
        printf("Desea atender el proximo usuario: ");
        if (scanf("%d", &respuesta) && respuesta) {
          puts("");
          printf("Se atendio: ");
          cola_proximo(cola);
          cola = cola_desencolar(cola, NULL);
        } else {
          puts("");
          char *dni = malloc(sizeof(char) * (LONGITUD_DNI + 1));
          printf("Ingrese el dni del usuario: ");
          if (scanf("%s", dni))
            puts("");
          
          int tiempo;
          printf(
              "Ingrese el tiempo que el usuario pago la membresia premium: ");
          if (scanf("%d", &(tiempo)))
            puts("");
          
          Usuario *usuario = usuario_crear(dni, tiempo);
          if (tablahash_buscar(tabla, usuario)) {
            cola = cola_desencolar(cola, usuario);
            printf("Se elimino de la cola el usuario ");
            usuario_imprimir(usuario);
          } else
            printf("  ¡El usuario no esta registrado en la empresa!\n");
        }
      } else
        printf("  ¡No hay usuarios en cola de espera!\n");
      puts("");

    } else {
      if (!cola_vacia(cola)) {
        printf("El proximo usuario a ser atendido es: ");
        cola_proximo(cola);
      } else
        printf("  ¡No hay usuarios en espera!\n");
      puts("");
    }
  }

  return 0;
}