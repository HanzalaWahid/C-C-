#include <stdio.h>
int main()
{
    int a = 0 + 1;
    int sum = 0;
    int avreage ;
    int square;

    printf("Fist ten Natural nmuber : \n");
    for ( i = 0 + 1; i <= 10; i++)
    {

        printf("%d   \n", i);
        sum = sum + i;
        avreage= sum/10;
        // square = a*a*a;
        
    }

    printf("The sum is: %d \n", sum);
    printf("The average is: %d\n", avreage);
    // printf("The square is: %d \n", square,(a*a*a));

    return 0;
}

// int a = 0 + 1 ;
// int sum = 0;
// printf("Fist ten Natural nmuber : \n");
// for (size_t i = 0 +1 ; i <= 10; i++)
// {

//     printf("%d \n",i);

//         sum = sum + i ;

// }
// printf("The sum is: %d",sum);
