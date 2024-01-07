#include <stdio.h>
int main()
{
    int a = 10, b = 5;
    int temp = a;
    a = b;
    b = temp;

    printf("After swaping , a = %d and b = %d \n", a, b);

    return 0;
}