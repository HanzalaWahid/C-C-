#include <stdio.h>
int main(){

    // break statement example
    for (int i = 0; i < 5; i++) {
        // If i is 3, exit the loop
        if (i == 3) {
            break;
        }
        printf("%d\n", i);
    }

    printf("\n");

    // continue statement example
    for (int i = 0; i < 5; i++) {
        // If i is 3, skip this iteration
        if (i == 3) {
            continue;
        }
        printf("%d\n", i);
    }

    return 0;
}
