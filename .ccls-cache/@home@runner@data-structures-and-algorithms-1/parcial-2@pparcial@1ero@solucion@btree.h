#ifndef __BTREE_H__
#define __BTREE_H__

typedef struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} * BTree;

typedef void (*FuncionVisitanteExtra)(int, void*);
BTree btree_crear();

void btree_destruir(BTree nodo);

BTree btree_unir(int dato, BTree left, BTree right);

void btree_foreach(BTree root, FuncionVisitanteExtra visit, void *extra);

#endif /* __BTREE_H__ */