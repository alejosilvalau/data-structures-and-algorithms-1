#include <stdio.h>
#include <stdlib.h>


// cd practica
// gcc -Wall 1er-parcial-2013-b.c -g -o main
// ./main


typedef struct _foos {
  int x, y;
} foos;
void foof(foos s) { s.x = 42; }
void arrf(int a[]) { a[0] = 42; }
void f(void) {
  foos s = {1, 2};
  int a[] = {1, 2};
  foof(s);
  arrf(a);
  printf("%d %d", s.x, a[0]);
}

int main() {
  f();
  return 0;
}
