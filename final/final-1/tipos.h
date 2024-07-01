#ifndef TIPOS_H
#define TIPOS_H

typedef void *(*FuncionCopiar)(void *dato);
typedef int (*FuncionComparar)(void *dato1, void *dato2);
typedef unsigned (*FuncionHashear)(void *dato);
typedef void (*FuncionDestruir)(void *dato);
typedef void (*FuncionVisitar)(void *dato);

#endif /* TIPOS_H */