#include <stdio.h>
#include <conio.h>
#include <math.h>

float sum(float, float, float, float, float);
float avg(float, float, float, float, float);
float st_d(float, float, float, float, float);

int main() {
    float n1, n2, n3, n4, n5;
    float Sum, Avg, Std;

    printf("Enter any 5 numbers: ");
    scanf("%f%f%f%f%f", &n1, &n2, &n3, &n4, &n5);

    Sum = sum(n1, n2, n3, n4, n5);
    printf("The sum of %f, %f, %f, %f, and %f is: %f\n", n1, n2, n3, n4, n5, Sum);

    Avg = avg(n1, n2, n3, n4, n5);
    printf("The avg of %f, %f, %f, %f, and %f is: %f\n", n1, n2, n3, n4, n5, Avg);

    Std = st_d(n1, n2, n3, n4, n5);
    printf("The standard deviation of %f, %f, %f, %f, and %f is: %f\n", n1, n2, n3, n4, n5, Std);

    getch(); // Use getch() to keep the console window open
    return 0;
}

float sum(float n1, float n2, float n3, float n4, float n5) {
    return (n1 + n2 + n3 + n4 + n5);
}

float avg(float n1, float n2, float n3, float n4, float n5) {
    return ((n1 + n2 + n3 + n4 + n5) / 5.0);
}

float st_d(float n1, float n2, float n3, float n4, float n5) {
    float x, y;
    x = (n1 + n2 + n3 + n4 + n5) / 5;

    // Check for division by zero before calculating square root
    if (n1 == x && n2 == x && n3 == x && n4 == x && n5 == x) {
        printf("Cannot calculate standard deviation - all numbers are the same.\n");
        return 0;
    }

    y = sqrt(((n1 - x) * (n1 - x) + (n2 - x) * (n2 - x) + (n3 - x) * (n3 - x) + (n4 - x) * (n4 - x) + (n5 - x) * (n5 - x)) / 4.0);
    return (y);
}
