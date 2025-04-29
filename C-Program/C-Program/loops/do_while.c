// 3. Do-While Loop
// Executes the code block at least once before checking the condition.

// do {
//     // code to be executed
// } while (condition);

#include <stdio.h>

int main() {
    int i = 1;
    do {
        printf("Hello %d\n", i);
        i++;
    } while (i <= 5);
    return 0;
}

// Output:

// Hello 1
// Hello 2
// Hello 3
// Hello 4
// Hello 5