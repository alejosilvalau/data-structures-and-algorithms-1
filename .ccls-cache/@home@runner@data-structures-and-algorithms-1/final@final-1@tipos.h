#ifndef TIPOS_H
#define TIPOS_H

typedef void *(*FunctionCopiar)(void *dato);
typedef int (*FunctionComparar)(void *dato1, void *dato2);
typedef int (*Predicado)(void *dato);
typedef unsigned (*FuncionHashear)(void *dato);

#endif /* TIPOS_H */