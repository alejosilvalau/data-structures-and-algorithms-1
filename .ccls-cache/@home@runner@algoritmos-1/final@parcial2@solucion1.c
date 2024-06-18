#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define CENTINELA ((Arbol23)1)

typedef struct arbol23_node Arbol23;

// Un nodo de Arbol23
// Si tiene un solo valor entonces right=CENTINELA
struct arbol23_node {
	int k1, k2;
struct arbol23_node left, middle, right;
};

// Devuelve un Arbol23 vacio
Arbol23 arbol23_crear() {
	return NULL;
}

// Devuelve la cantidad de valores del nodo raiz del arbol t
static int cantidad_de_valores(Arbol23 t) {
	assert(t != NULL);
	return t->right == CENTINELA ? 1 : 2;
}

// Crea un nodo con un valor (y dos hijos)
static Arbol23 crear_nodo_binario(int x, Arbol23 l, Arbol23 r) {
	Arbol23 nodo = malloc(sizeof(*nodo));
	nodo->k1 = x;
	nodo->left = l;
	nodo->middle = r;
	nodo->right = CENTINELA;
	return nodo;
}

// Inserta el valor x en el arbol t
// - Si el nodo raiz de t se rebalsa, devuelve 1 y guarda el arbol izquierdo en
//   *out_l, el derecho en *out_r y el valor del medio en *out_x
// - Si no, devuelve 0 y guarda NULL en *out_l y *out_r
// El caso que (t == NULL) se considera un rebalse.
static int insertar_impl(Arbol23 t, int x, int* out_x, Arbol23* out_l, Arbol23* out_r) {

	*out_l = NULL;
	*out_r = NULL;
	int rebalse = 0;

	if (t == NULL) {
		*out_x = x;
		rebalse = 1;
	} else if (cantidad_de_valores(t) == 1) {

		Arbol23 l, r;
		if (x < t->k1) {
			if (insertar_impl(t->left, x, &x, &l, &r)) {
				t->k2 = t->k1;
				t->k1 = x;
				t->right = t->middle;
				t->left = l;
				t->middle = r;
			}
		} else if (t->k1 < x) {
			if (insertar_impl(t->middle, x, &x, &l, &r)) {
				t->k2 = x;
				t->middle = l;
				t->right = r;
			}
		}

	} else {

		Arbol23 l, r;
		if (x < t->k1) {
			if (insertar_impl(t->left, x, &x, &l, &r)) {
				*out_l = crear_nodo_binario(x, l, r);
				*out_x = t->k1;
				*out_r = crear_nodo_binario(t->k2, t->middle, t->right);
				free(t);
				rebalse = 1;
			}
		} else if (t->k1 < x && x < t->k2) {
			if (insertar_impl(t->middle, x, &x, &l, &r)) {
				*out_l = crear_nodo_binario(t->k1, t->left, l);
				*out_x = x;
				*out_r = crear_nodo_binario(t->k2, r, t->right);
				free(t);
				rebalse = 1;
			}
		} else if (t->k2 < x) {
			if (insertar_impl(t->right, x, &x, &l, &r)) {
				*out_l = crear_nodo_binario(t->k1, t->left, t->middle);
				*out_x = t->k2;
				*out_r = crear_nodo_binario(x, l, r);
				free(t);
				rebalse = 1;
			}
		}
	}

	return rebalse;
}

// Inserta el valor x en el arbol t. Devuelve la nueva raiz.
Arbol23 arbol23_insertar(Arbol23 t, int x) {
	Arbol23 l, r;
	if (insertar_impl(t, x, &x, &l, &r))
		t = crear_nodo_binario(x, l, r);
	return t;
}