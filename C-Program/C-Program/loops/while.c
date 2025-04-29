// 2. While Loop
// Used when the number of iterations is not known and depends on a condition.

// while (condition) {
//     // code to be executed
// }


#include <stdio.h>

int main() {
    int i = 1;
    while (i <= 5) {
        printf("Count: %d\n", i);
        i++;
    }
    return 0;
}


// Output:

// Count: 1
// Count: 2
// Count: 3
// Count: 4
// Count: 5