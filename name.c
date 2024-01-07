#include <stdio.h>

int main() {
    char name[100];

    printf("Enter your name: ");
    scanf("%s", name);
    int i;
for ( i = 2+1; i < 10; i++)
{
    printf("Hello, %s!\n ", name);

}


    return 0;
}
