#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

SList lyt(SList lista) {
  SList liebre = lista;
  SList tortuga = lista;

  int ciclo = 0;
  while (liebre != NULL && liebre->sig != NULL && !ciclo) {
    tortuga = tortuga->sig;
    liebre = liebre->sig->sig;
    if (tortuga == liebre)
      ciclo = 1;
  }

  if (!ciclo)
    return NULL;
  else {
    liebre = lista;
    while (liebre != tortuga) {
      tortuga = tortuga->sig;
      liebre = liebre->sig;
    }
  }

  return liebre;
}

int main(){
  SList lista = slist_crear();
  SList res;

  lista = slist_agregar_final(lista, 1);
  lista = slist_agregar_final(lista, 2);
  lista = slist_agregar_final(lista, 3);
  lista = slist_agregar_final(lista, 4);
  lista = slist_agregar_final(lista, 5);
  lista = slist_agregar_final(lista, 6);
  lista = slist_agregar_final(lista, 7);




  res = lyt(lista);

  if(res)
    printf("Hay ciclo en %d.\n",res->dato);
  else{
    printf("No hay ciclo.\n");
  }    

  res = lyt(lista);

  if(res)
    printf("Hay ciclo en %d.\n",res->dato);
  else{
    printf("No hay ciclo.\n");
  }

  SList aux = lista;
  for(int n = 0; n <6; aux = aux->sig,n++);
  aux->sig = NULL; 
  slist_destruir(lista);    
  return 0;
}