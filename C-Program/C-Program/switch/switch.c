// implement switch case

#include <stdio.h>

int main() {
    int choice;

    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You chose option 1\n");
            break;
        case 2:
            printf("You chose option 2\n");
            break;
        case 3:
            printf("You chose option 3\n");
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

//  Difference between break and continue

//  break: It immediately terminates the switch statement and transfers the control to the statement immediately following the switch statement.

//  continue: It skips the remaining statements in the current case block and transfers the control to the next iteration of the switch statement.