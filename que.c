// find the total marks of studemt in five subjects and the average marks as well . write a function that receiver 5 integers and return the sum and average of numbers

#include <stdio.h>

void calcuate(int arr[], int *sum, float *average)
{
    *sum = 0;
    for (int i = 0; i < 5 ;i++)
    {
        *sum += arr[i];
    }
    *average = (float)(*sum) / 5;
}

int main()
{
    int marks[5], sum = 0;
    float average;

    for (int i = 0; i < 5; i++)
    {

        printf("Enter marks for suject  %d: \n", i + 1);
        scanf("%d", &marks[i]);
    }

    calcuate(marks,&sum, &average);

    printf("The sum of student is : %d \n", sum);
    printf("The average of student is: %.2f \n", average);

    return 0;
}
