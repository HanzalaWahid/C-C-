// Variable Declaration and Initialization in C
// 1. Identifier names must start with a letter or an underscore (_).
// 2. They can contain letters, digits, or underscores.
// 3. They must not start with a digit.
// 4. They are case-sensitive.
// 5. Use descriptive and meaningful names (e.g., myInt, myFloat).
// 6. Avoid using reserved words (e.g., int, float, char).
// 7. Use camelCase for naming variables.

#include <stdio.h>

int main() {
    int myInt = 10;          // Integer variable
    float myFloat = 3.14;    // Float variable
    double myDouble = 2.71;  // Double variable
    char myChar = 'A';       // Character variable

    // Print the values of the variables
    printf("myInt: %d\n", myInt);
    printf("myFloat: %.2f\n", myFloat);
    printf("myDouble: %.2f\n", myDouble);
    printf("myChar: %c\n", myChar);

    return 0;
}
