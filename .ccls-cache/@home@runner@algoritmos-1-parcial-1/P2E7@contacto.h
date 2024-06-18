#ifndef __CONTACTO_H__
#define __CONTACTO_H__

typedef struct {
    char* nombre;
    char* tel;
    unsigned int edad;
} Contacto;

/**
 * Crea un nuevo contacto.
 */
Contacto* contacto_crear ();

/**
 * Crea una copia física del contacto.
 */
Contacto* contacto_copia (Contacto* contacto);

/**
 * Compara dos contactos. Devuelve 0 si son iguales, 1 si no lo son.
 */
int contacto_comparar (Contacto* c1, Contacto* c2);

/**
 * Dado un número, devuelve 1 si el contacto es mayor a esa edad y 0 si no.
 */
int contacto_es_mayor_de (Contacto* contacto, unsigned int edad);

/**
 * Función destructora de un contacto.
 */
void contacto_destruir (Contacto* contacto);

/**
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir (Contacto* contacto);



#endif /* __CONTACTO_H__ */