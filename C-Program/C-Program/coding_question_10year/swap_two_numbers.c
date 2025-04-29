# include <stdio.h>
int main(){

    // swap using and temporary variables
    int a = 5 , b = 10 ;
    printf("Before swapping the value of a = %d and b = %d \n " , a, b);
    int temp = a;
    a = b ;
    b = temp  ; 
    printf("After swapping the value of a = %d and b = %d  " , a, b); 
    
    // swap using addition and subtract 
    a = a + b ;
    b = a - b ;
    a = a - b ;
    printf("\nAfter swapping the value of a = %d and b = %d  " , a, b);

    // swap using XOR

    a = a ^ b ;
    b = a ^ b ;
    a = a ^ b ;
    printf("\nAfter swapping the value of a = %d and b = %d  " , a, b);

    return 0;
}