#include <stdio.h>

int main() {
    int x = 5;
    int y = (x > 3) ? 10 : 0; // ternary operator
    int *ptr = &x;            // address operator
    int value = *ptr;         // pointer dereference

    // ternary operator
    printf("Ternary Operator Result: %d\n", y);

    // address operator
    printf("Address of x: %p\n", ptr);

    // pointer dereference
    printf("Value at Address: %d\n", value);

    return 0;
}
