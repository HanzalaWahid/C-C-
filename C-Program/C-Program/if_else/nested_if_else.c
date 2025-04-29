#include <stdio.h>

int main() {
    int x = 5;

    // nested if-else statement
    if (x > 0) {
        printf("x is positive\n");
        if (x % 2 == 0) {
            printf("x is even\n");
        } else {
            printf("x is odd\n");
        }
    } else {
        printf("x is negative\n");
    }

    return 0;
}
