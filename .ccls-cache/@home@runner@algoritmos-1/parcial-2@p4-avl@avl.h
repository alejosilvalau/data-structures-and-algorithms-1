#ifndef __AVL_H__
#define __AVL_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  AVL_RECORRIDO_IN,  /** Inorden */
  AVL_RECORRIDO_PRE, /** Preorden */
  AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;


typedef struct _AVL_Nodo {
  void *dato;
  struct _AVL_Nodo *izq, *der;
  int altura;
} AVL_Nodo;

struct _AVL {
  AVL_Nodo *raiz;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
};

typedef struct _AVL *AVL;
/**
 * Retorna un arbol AVL vacio
 */
AVL avl_crear(FuncionCopiadora, FuncionComparadora, FuncionDestructora);

/**
 * Destruye el arbol y sus datos.
 */
void avl_destruir(AVL);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
int avl_buscar(AVL, void *);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad de los
 * arboles AVL.
 */
void avl_insertar(AVL, void *);

/**
 * Retorna 1 si el arbol cumple la propiedad de los arboles AVL, y 0 en caso
 * contrario.
 */
int avl_validar(AVL);

/**
 * Recorrido DSF del arbol
 */
void avl_recorrer(AVL, AVLRecorrido, FuncionVisitanteExtra, void *);

AVL_Nodo *avl_eliminar(AVL_Nodo *raiz, void *dato, FuncionCopiadora copia, FuncionComparadora comp);

#endif /* __AVL_H__*/