#include "contacto.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Crea un nuevo contacto.
 */
Contacto* contacto_crear (char* nombre, char* telefono, unsigned int edad){
    Contacto* nuevo = malloc(sizeof(Contacto));

    nuevo->nombre = malloc(sizeof(char) * (strlen(nombre)+1));
    strcpy(nuevo->nombre, nombre);

    nuevo->tel = malloc(sizeof(char) * (strlen(telefono)+1));
    strcpy(nuevo->tel, telefono);

    nuevo->edad = edad;

    return nuevo;
}

/**
 * Crea una copia física del contacto.
 */
Contacto* contacto_copia (Contacto* contacto){
    Contacto* copia = contacto_crear(contacto->nombre, contacto->tel, contacto->edad);
    return copia;
}

/**
 * Compara dos contactos. Devuelve 0 si son iguales, 1 si no lo son.
 */
int contacto_comparar (Contacto* c1, Contacto* c2){
    if (strcmp(c1->nombre, c2->nombre))
        return 1;
    if (strcmp(c1->tel, c2->tel))
        return 1;
    if (c1->edad == c2->edad)
        return 0;
    return 1;
}

/**
 * Dado un número, devuelve 1 si el contacto es mayor a esa edad y 0 si no.
 */
int contacto_es_mayor_de (Contacto* contacto, unsigned int edad){
    return (contacto->edad >= edad);
}

/**
 * Función destructora de un contacto.
 */
void contacto_destruir (Contacto* contacto){
    free(contacto->nombre);
    free(contacto->tel);
    free(contacto);
}

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir (Contacto* contacto){
    printf("%s, %s, %d.\n", contacto->nombre, contacto->tel, contacto->edad);
}
