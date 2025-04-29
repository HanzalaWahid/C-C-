#include <stdio.h>
int main(){

int num;

printf("Enter any number: \n");
scanf("%d",&num);

if (num > 0){
    printf("The number is positive");
    if (num % 2 == 0){
        printf(" and even.");
    }
    else{
        printf(" and odd.");
    }
}

else if (num == 0){
    printf("The number is zero.");
}

else{
    printf("The number is negative.");
}

return 0;

}