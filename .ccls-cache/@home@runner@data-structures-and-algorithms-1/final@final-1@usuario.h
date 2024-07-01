#ifndef __USUARIO_H__
#define __USUARIO_H__

typedef struct _Usuario {
  char *dni;
  int tiempo;
} Usuario;

/**
* Crea un nuevo usuario.
*/
Usuario *usuario_crear(char* dni, int tiempo);

/**
* Retorna 0 si dos usuarios tienen el mismo nombre.
*/
int usuario_comparar(Usuario *u1, Usuario *u2);

/**
* Retorna una copia del usuario pasado como argumento
*/
Usuario *usuario_copiar(Usuario *u);

/**
* Retorna hash correspondiente al dni del usuario
*/
unsigned usuario_hashear(Usuario *u);

#endif /* __USUARIO_H__ */