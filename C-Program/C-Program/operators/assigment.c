#include <stdio.h>

int main() {
    int a = 10;
    int b = 5;

    // assignment
    a = b;
    printf("Assignment (=): %d\n", a);

    // addition assignment
    a += b;
    printf("Addition Assignment (+=): %d\n", a);

    // subtraction assignment
    a -= b;
    printf("Subtraction Assignment (-=): %d\n", a);

    // multiplication assignment
    a *= b;
    printf("Multiplication Assignment (*=): %d\n", a);

    // division assignment
    a /= b;
    printf("Division Assignment (/=): %d\n", a);

    // modulus assignment
    a %= b;
    printf("Modulus Assignment (%%=): %d\n", a);

    return 0;
}
