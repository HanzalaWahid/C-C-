#include <stdio.h>
int main (){
    int marks[3];

    printf("Enter your marks: ");
    
    for (int i = 0; i < 6; i++) {
        scanf("%d", &marks[i]);
    }
        for (int i = 0; i < 6; i++) {
        printf("The marks of student %d is: %d\n", i, marks[i]);
    }



    return 0 ;
}