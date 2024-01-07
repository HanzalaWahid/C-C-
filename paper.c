#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char str[100];
    char find, replace;

    printf("Enter a string: ");
    scanf("%(^/n)s", str);

    printf("Enter a find: ");
    scanf("%(^/n)s", &find);

    printf("Enter a replace: ");
    scanf("%(^/n)s", &replace);

    int length = strlen (str);
    for (int  i = 0; i < length; i++)
    {
        if (str[i] == find)
        {
            (str[i] == replace);
        }
         
         printf(" Updated String \n");
         printf("%s \n",str);
    }
     

    return 0;
}