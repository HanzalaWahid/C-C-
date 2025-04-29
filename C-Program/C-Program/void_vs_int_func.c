// Difference Between void main() and int main()

// int main() returns an integer value to the operating system, indicating the exit status of the program. It is the standard form as per C standards.
// void main() does not return any value, but it is not considered standard in modern C programming.

// Example with int main():

#include <stdio.h>

int main() {
    printf("This is int main().\n");
    return 0;
}
// Example with void main():

#include <stdio.h>

void main() {
    printf("This is void main().\n");
}



// Key Difference:

// int main() is recommended because it conforms to the standard and provides an exit status.
// void main() is compiler-dependent and not recommended for portable code.
