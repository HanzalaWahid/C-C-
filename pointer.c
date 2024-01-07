#include <stdio.h>

int main() {
    int age = 22;
    int *ptr = &age; 
    int age2 = *ptr;

    printf("Address: %p\n", (void *)&age); 

    return 0;
}
