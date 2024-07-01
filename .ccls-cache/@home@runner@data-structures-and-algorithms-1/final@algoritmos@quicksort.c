#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int largo) {
  for (int i = 0; i < largo; i++) {
    printf("%d, ", arr[i]);
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

  quickSort(arr, 0, 9);

  printf("Post ordernamiento: \n");
  print_array(arr, 10);
  printf("\n");

  return 0;
}