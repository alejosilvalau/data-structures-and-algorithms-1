typedef struct _BHeap {
void **arr;
int capacidad;
int ultimo;
FuncionComparadora comp;
} *BHeap;