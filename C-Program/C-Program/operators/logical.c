#include <stdio.h>

int main() {
    int x = 5, y = 3;

    // logical AND
    printf("Logical AND (&&): %d\n", (x > 0) && (y > 0));

    // logical OR
    printf("Logical OR (||): %d\n", (x > 0) || (y < 0));

    // logical NOT
    printf("Logical NOT (!): %d\n", !(x > 0));

    return 0;
}
