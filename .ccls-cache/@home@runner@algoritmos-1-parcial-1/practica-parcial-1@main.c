#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_reverse(char *str) {
  int largo = strlen(str);
  char strRev[largo + 1];
  for (int i = 0; i < largo; i++) {
    strRev[i] = str[largo - 1 - i];
  }
  strRev[largo] = '\0';

  printf("%s\n", str);
  printf("%s", strRev);
}

int main() {

  char str[] = "Hello World";

  string_reverse(str);

  return 0;
}
