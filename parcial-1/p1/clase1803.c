#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* get_new_line () {
    char* line = malloc(sizeof(char) * 100);
    fgets(line, 100, stdin);
    int largo = strlen(line);

    while (line[largo-1] != '\n') {
        line = realloc(line, sizeof(char) * (largo+100));
        fgets(line + largo, 100, stdin);
        largo += strlen(line + largo);
    }

    line[largo-1] = '\0';
    line = realloc(line, sizeof(char) * largo);
    return line;
}

typedef struct {
    char* nombre;
    char* telefono;
    unsigned int edad;
} Contacto;

Contacto crear_contacto () {
    Contacto nuevo_contacto;
    printf("Ingrese un nuevo nombre: ");
    nuevo_contacto.nombre = get_new_line();
    printf("Ingrese un nuevo telefono: ");
    nuevo_contacto.telefono = get_new_line();
    printf("Ingrese una nueva edad: ");
    scanf("%d%*c", &nuevo_contacto.edad);
    
    return nuevo_contacto;
}

Contacto* crear_contacto_puntero () {
    Contacto* nuevo_contacto = malloc(sizeof(Contacto));
    printf("Ingrese un nuevo nombre: ");
    nuevo_contacto->nombre = get_new_line();
    printf("Ingrese un nuevo telefono: ");
    nuevo_contacto->telefono = get_new_line();
    printf("Ingrese una nueva edad: ");
    scanf("%d", &(nuevo_contacto->edad));
    
    return nuevo_contacto;
}

void actualizar_edad_puntero (Contacto* contacto) {
    printf("Ingrese una nueva edad: ");
    scanf("%d", &(contacto->edad));
}

void actualizar_edad (Contacto contacto) {
    printf("Ingrese una nueva edad: ");
    scanf("%d", &(contacto.edad));
}

void imprimir_contacto (Contacto contacto) {
    printf("Nombre: %s \nTelefono: %s \nEdad: %d \n", contacto.nombre, contacto.telefono, contacto.edad);
}

void liberar_contacto (Contacto contacto) {
    free(contacto.nombre);
    free(contacto.telefono);
}

int main(){

    Contacto contacto = crear_contacto();
    Contacto* p_contacto = crear_contacto_puntero();

    printf("contacto:\n");
    imprimir_contacto(contacto);

    printf("p_contacto:\n");
    imprimir_contacto(*p_contacto);

    actualizar_edad(contacto);
    actualizar_edad_puntero(p_contacto);

    printf("contacto:\n");
    imprimir_contacto(contacto);

    printf("p_contacto:\n");
    imprimir_contacto(*p_contacto);

    liberar_contacto(contacto);
    liberar_contacto(*p_contacto);
    free(p_contacto);

    return 0;
}