#include <stdio.h>
#include <string.h>

struct bank
{
    char name[50];
    int account;
    float balance;
};

int main()
{
    struct bank C1;

    strcpy(C1.name ,"Hanzala");
    C1.account = 1090414222;
    C1.balance = 2223456.6543;

    printf("Name: %s \n ", C1.name);
    printf("Account Number: %d\n", C1.account);
    printf("Balance: %.2f\n", C1.balance);

    return 0;
}