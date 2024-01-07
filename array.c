#include <stdio.h>

int main() {
    const double ABSOLUTE_ZERO_CELSIUS = -273.15;
    const double ABSOLUTE_ZERO_FAHRENHEIT = -459.67;

    int choice;
    double celsius, fahrenheit, kelvin;

    printf("TEMPERATURE UNIT CONVERSION:\n");
    printf("01. Celsius to Fahrenheit\n");
    printf("02. Fahrenheit to Celsius\n");
    printf("03. Celsius to Kelvin\n");
    printf("04. Kelvin to Celsius\n");
    printf("05. Fahrenheit to Kelvin\n");
    printf("06. Kelvin to Fahrenheit\n\n");
    printf("Enter your choice (01 to 06): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter temperature in Celsius: ");
            scanf("%lf", &celsius);
            fahrenheit = (celsius * 9 / 5) + 32;
            printf("Temperature in Fahrenheit will be: %.2lf\n", fahrenheit);
            break;

        case 2:
            printf("Enter temperature in Fahrenheit: ");
            scanf("%lf", &fahrenheit);
            celsius = (fahrenheit - 32) * 5 / 9;
            printf("Temperature in Celsius will be: %.2lf\n", celsius);
            break;

        case 3:
            printf("Enter temperature in Celsius: ");
            scanf("%lf", &celsius);
            kelvin = celsius + 273.15;
            printf("Temperature in Kelvin will be: %.2lf\n", kelvin);
            break;

        case 4:
            printf("Enter temperature in Kelvin: ");
            scanf("%lf", &kelvin);
            celsius = kelvin - 273.15;
            printf("Temperature in Celsius will be: %.2lf\n", celsius);
            break;

        case 5:
            printf("Enter temperature in Fahrenheit: ");
            scanf("%lf", &fahrenheit);
            kelvin = (fahrenheit + ABSOLUTE_ZERO_FAHRENHEIT) * 5 / 9;
            printf("Temperature in Kelvin will be: %.2lf\n", kelvin);
            break;

        case 6:
            printf("Enter temperature in Kelvin: ");
            scanf("%lf", &kelvin);
            fahrenheit = (kelvin * 9 / 5) + ABSOLUTE_ZERO_FAHRENHEIT;
            printf("Temperature in Fahrenheit will be: %.2lf\n", fahrenheit);
            break;

        default:
            printf("\n\nINVALID CHOICE\n\nPLEASE TRY AGAIN\n\nTHANK YOU\n");
    }

    return 0;
}
