// check if the num1 is greater than , less than and equals to num2

# include <stdio.h>

int main(){

int num1 , num2;
printf("Enter number one: \n");
scanf("%d",&num1);

printf("Enter number two: \n");
scanf("%d",&num2);

if (num1 > num2 ){
    printf("%d is greater than %d" , num1, num2);
}

else if ( num1 < num2){
    printf("%d is less than %d" , num1, num2);
}

else{
    printf("%d is equal to %d" , num1, num2);
}

return 0 ;

}