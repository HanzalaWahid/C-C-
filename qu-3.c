#include <stdio.h>

void calculate(int num1, int num2, int num3, int num4, int num5, int *sum, float *average);

 int main()
{

    int num1, num2, num3, num4, num5, sum;
    float average;

    printf("Enter marks of first subject ");
    scanf("%d ", &num1);
    printf("Enter marks of second subject ");
    scanf("%d ", &num2);
    printf("Enter marks of third subject ");
    scanf("%d ", &num3);
    printf("Enter marks of fourth subject ");
    scanf("%d ", &num4);
    printf("Enter marks of fifth subject ");
    scanf("%d ", &num5);

    calculate(num1, num2, num3, num4, num5, &sum, &average);

        printf("The sum of student 1 is : %d", sum);
    printf("The average of student 1 is : %.2f", average);

    return 0;
}
    void calculate(int num1, int num2, int num3, int num4, int num5, int *sum, int *average)
{
        *sum = num1 + num2 + num3 + num4 + num5;
    *average = (float)(*sum) / 5;
}