// C Program to illustrate the working of modulo operator
#include <stdio.h>

// gcc -Wall modulo.c -g -o main
// ./main

int main(void)
{
    int x, y;

    int result;

    x = 602190259;
    y = 11;
    // using modulo operator
    result = x % y;
    printf("%d\n", result);

    return 0;
}