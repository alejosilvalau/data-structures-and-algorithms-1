#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int largo) {
  for (int i = 0; i < largo; i++) {
    printf("%d, ", arr[i]);
  }
}

int busqueda_binaria(int arr[], int lo, int hi, int v) {
  if (hi < lo)
    return -1;

  int medio = (lo + hi) / 2;

  if (arr[medio] == v)
    return medio;
  else if (arr[medio] < v)
    return busqueda_binaria(arr, medio + 1, hi, v);
  else
    return busqueda_binaria(arr, lo, medio - 1, v);
}

void bubble(int arr[], int largo) {
  bool hiceAlgo = true;
  while (hiceAlgo) {
    hiceAlgo = false;
    for (int i = 0; i < (largo - 1); i++) {
      if (arr[i] > arr[i + 1]) {
        int aux = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = aux;
        hiceAlgo = true;
      }
    }
  }
}

void insertion_sort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (arr[j] > arr[j + 1]) {
        int aux = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = aux;
      }
    }
  }
}

void selection_sort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++)
      if (arr[j] < arr[min]) {
        min = j;
      }
    int aux = arr[i];
    arr[i] = arr[min];
    arr[min] = aux;
  }
}

int *mezclar(int *arr1, int *arr2, int largo1, int largo2) {
  int *arr3 = (int *)malloc(sizeof(int) * (largo1 + largo2));
  int i = 0, j = 0, k = 0;

  while (i < largo1 && j < largo2) {
    if (arr1[i] < arr2[j]) {
      arr3[k] = arr1[i];
      i++;

    } else {
      arr3[k] = arr2[j];
      j++;
    }
    k++;
  }
  while (i < largo1) {
    arr3[k] = arr1[i];
    i++;
    k++;
  }

  while (j < largo2) {
    arr3[k] = arr2[j];
    j++;
    k++;
  }
  return arr3;
}

int *merge_sort(int *arr, int largo) {
  if (largo < 2) {
    return arr;
  } else {
    int medio = largo / 2;
    int *arr1 = (int *)malloc(sizeof(int) * medio);
    int *arr2 = (int *)malloc(sizeof(int) * (largo - medio));

    for (int i = 0; i < medio; i++) {
      arr1[i] = arr[i];
    }
    for (int i = medio; i < largo; i++) {
      arr2[i - medio] = arr[i];
    }

    int *arr1b = merge_sort(arr1, medio);
    int *arr2b = merge_sort(arr2, largo - medio);

    return mezclar(arr1b, arr2b, medio, largo - medio);
  }
}



void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int particionar(int arr[], int ini, int fin) {

  int pivote = arr[fin];

  int i = (ini - 1);

  for (int j = ini; j < fin; j++) {
    if (arr[j] <= pivote) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[fin]);
  return (i + 1);
}

void quickSort(int arr[], int ini, int fin) {
  if (ini < fin) {
    int pivote = particionar(arr, ini, fin);
    quickSort(arr, ini, pivote - 1);
    quickSort(arr, pivote + 1, fin);
  }
}

int main() {
  int *arr = malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    int num = rand() % 100 + 1;
    arr[i] = num;
  }

  printf("Pre ordernamiento: \n");
  print_array(arr, 10);
  printf("\n");

  // arr = merge_sort(arr, 10);

  quickSort(arr, 0, 9);

  printf("Post ordernamiento: \n");
  print_array(arr, 10);
  printf("\n");

  return 0;
}