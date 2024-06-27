#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_unir(char *arregloStrings[], int n, char *sep, char *res) {
  for (int i = 0; i < n; i++) {
    strcat(res, arregloStrings[i]);

    if (i < n - 1) {
      strcat(res, sep);
    }
  }
}

int main() {
  char *arregloStrings[] = {"hola", "chau", "este"};
  int tam = 2;
  char *sep = "2";
  char *res = malloc(sizeof(char) * (tam * strlen(sep) + 1));
  string_unir(arregloStrings, tam, sep, res);
  printf("%s\n", res);
  return 0;
}