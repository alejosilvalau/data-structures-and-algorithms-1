#include "stdio.h"

void f1 (char *s, char c) {
  * (s + 2) = c;
  printf("%s\n", s);
}

int main(){ 
  char a[] = "cadena", **b, *c;

  c = a;
  b = &c; 
  f1(*b, 'y');

  *b = * b + 2;
  f1(c,'m');

 return 0;

}