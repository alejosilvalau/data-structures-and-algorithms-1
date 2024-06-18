typedef struct _Heap {
int* data;
int cantidad, capacidad;
} * Heap;

void swap_int(int* x, int* y);

void heap_insertar(Heap heap, int dato);

void heap_eliminar(Heap heap);

int padre(int i);
int hijo_izq(int i);
int hijo_der(int i);

void flotar(int* arr, int i, int n);
void hundir(int* arr, int i, int n);
