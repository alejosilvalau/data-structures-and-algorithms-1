#include "btree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  if (orden == BTREE_RECORRIDO_IN){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_PRE){
    if (arbol == NULL) { 
      return;
    }
    else {
      visit(arbol->dato);
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
    }
  }
  if (orden == BTREE_RECORRIDO_POST){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer(arbol->left, orden, visit);
      btree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
    }
  }
  return;
}

// ejercicio 3 

int btree_nnodos(BTree arbol){
  int n = 0;
  if (arbol == NULL) { 
      return n;
    }
  else {
      n += 1;
      printf("%d\n", arbol->dato);
      n += btree_nnodos(arbol->left);
      n += btree_nnodos(arbol->right);
    }
    return n;
}

// buscar

int comparar(int valor, int valor2){
  if (valor == valor2){
    return 1;
  }
  else return 0;
}

int btree_buscar(BTree arbol, int valor, FuncionVisitante2 visit){
  int n = 0;
  if (arbol == NULL) { 
      return 0;
    }
    else {
      btree_buscar(arbol->left, valor, visit);
      n = visit(arbol->dato, valor);
      if(n == 1){
	return n;
      }
      btree_buscar(arbol->right, valor, visit);
    }
    return n;
}

// comparar

BTree btree_copiar(BTree arbol){
  BTree narbol = btree_crear();
  
  if (arbol == NULL){
    return narbol;
  }
  
  else {
    narbol = btree_unir(arbol->dato, btree_copiar(arbol->left), btree_copiar(arbol->right));
  }
  
  return narbol;
}

// altura

int max(int num1, int num2){
  if (num1 > num2) {
    return num1;
  }
  else {
    return num2;
  }
}

int btree_altura(BTree arbol){
  int altura;
  if (arbol == NULL){
    altura = -1;
    return altura;
  }
  else {
    int altura_izq = btree_altura(arbol->left);
    int altura_der = btree_altura(arbol->right);
    return max(altura_izq, altura_der) + 1;
  }
}

// nodos en profundidad n

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if (arbol == NULL){
    return 0;
  }
  else if (profundidad == 0){
    return 1;
  }
  else {
    return btree_nnodos_profundidad(arbol->left, profundidad-1) + btree_nnodos_profundidad(arbol->right, profundidad - 1);
  }
}

// profundidad

int btree_profundidad(BTree arbol, int dato, int prof){
  if(arbol == NULL){
    return -1;
  }
  if(arbol->dato == dato){ 
    return prof;
  }
  int n = btree_profundidad(arbol->left, dato, prof+1);
  if(n == -1){
    return btree_profundidad(arbol->right, dato, prof+1);
  }
  else{
    return n;
  }
}
  
// sumar

int btree_sumar(BTree arbol){
  if (arbol == NULL) {
    return 0;
  }
  else {
    return arbol->dato + btree_sumar(arbol->left) + btree_sumar(arbol->right);
  }
}



void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void *extra){
  if (orden == BTREE_RECORRIDO_IN){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
    }
  }
  if (orden == BTREE_RECORRIDO_PRE){
    if (arbol == NULL) { 
      return;
    }
    else {
      visit(arbol->dato, extra);
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
    }
  }
  if (orden == BTREE_RECORRIDO_POST){
    if (arbol == NULL) { 
      return;
    }
    else {
      btree_recorrer_extra(arbol->left, orden, visit, extra);
      btree_recorrer_extra(arbol->right, orden, visit, extra);
      visit(arbol->dato, extra);
    }
  }
  return;
}

// ejercicio 5


int aux(BTree arbol, FuncionVisitante visit, int profundidad){
  if(arbol == NULL){
    return 0;
    //printf("-0\n");
  }
  else if(profundidad == 0){
    //printf("-1\n");
    visit(arbol->dato);
    //puts("");
    //printf("-2\n");
    return 1;
  }
  else{
    //printf("-3\n");
    return aux(arbol->left, visit, profundidad-1) + aux(arbol->right, visit, profundidad-1);
  }
}

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit, int n){
  int altura = btree_altura(arbol);
  //printf("a\n");
  if(n != altura){
    //printf("b\n");
    int Nnodos = btree_nnodos_profundidad(arbol, n);
    //printf("c\n");
    int hor = aux(arbol, visit, n);
    //printf("d\n");
    if(hor == Nnodos){
      //printf("e\n");
      btree_recorrer_bfs(arbol, visit, n+1);
    }
  }
  else{
    //printf("f\n");
    aux(arbol, visit, n);
    return;
  }
}


