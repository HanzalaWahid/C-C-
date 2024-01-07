#include <stdio.h>

void calculate(int arr[], int *sum, float *average) {

    *sum = 0;
    for (int i = 0; i < 5; i++) 
    {
        *sum += arr[i];
    }
    *average = (float)(*sum) / 5;
}

int main() {
    int marks[5], sum = 0;
    float average;

    for (int i = 0; i < 5; i++) {
        printf("Enter marks for subject %d: ", i + 1);
        scanf("%d", &marks[i]);
    }

    calculate(marks, &sum, &average);

    printf("The sum of student is: %d\n", sum);
    printf("The average of student is: %.2f\n", average);

    return 0;
}
