#include <stdlib.h>
#include <string.h>

void bubble_sort(float *arreglo, int longitud) {
    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}

float mediana(float *arreglo, int longitud) {
    if (longitud == 0) {
        return 0.0f; 
    }

    // Creamos una copia del arreglo original para no modificarlo
    float *copia = (float*) malloc(longitud * sizeof(float));
    memcpy(copia, arreglo, longitud * sizeof(float));

    // Ordenamos la copia
    bubble_sort(copia, longitud);

    int indiceMitad = longitud / 2;
    float resultado;
    if (longitud % 2 == 0) {
        resultado = ((copia[indiceMitad - 1] + copia[indiceMitad]) / 2.0f); 
    } else {
        resultado = copia[indiceMitad];
    }

    // Liberamos la memoria de la copia
    free(copia);

    return resultado;
}
