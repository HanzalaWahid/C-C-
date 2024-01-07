// #include <stdio.h>
// int printTable(int table);

// int main()
// {
//     int a = 5;
//     printTable(a);
//     return 0;
// }
// int printTable(int table)
// {
//     int i;
//     for (i = 0; i <= 10; i++)
//     {
//         printf("%d * %d = %d \n", table, i, table * i);
//     }
// }

#include <stdio.h>
int sum( int a,int b);

int main (){

    int a = 5;
    int b = 6;

 int  total = sum(a,b);
     printf("%d + %d = %d \n" , a, b, total);

    return 0; 
}
int sum( int a, int b){

    printf("Enter two number: \n ");
    return a+b;
}