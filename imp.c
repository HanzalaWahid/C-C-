#include <stdio.h>
#include <string.h>

#define max_customers 200

struct customer
{
    long long accNo;
    char name[50];
    int balance;
};

void balanceLessThan100(struct customer customers[]);

int main()
{
    struct customer customers[max_customers];
    long long accNo;
    char name[50];
    int balance;

    for (int i = 0; i < 2; i++)
    {
        printf("Enter account number: ");
        scanf("%lld", &customers[i].accNo);
        printf("Enter name: ");
        scanf(" %[^\n]49s", customers[i].name); // <-- Corrected line
        printf("Enter Balance:");
        scanf("%d", &customers[i].balance);
    }

    // balanceLessThan100(customers);
    int code;
    printf("Enter account number: ");
    scanf("%lld", &accNo);
    printf("Enter amount: ");
    scanf("%d", &balance);
    printf("Enter 1 for deposit & 0 withdrawal: ");
    scanf("%d", &code);

    int accountfound; // using this as a flag
    for (int i = 0; i < max_customers; i++)
    {
        if (accNo == customers[i].accNo)
        {
            accountfound = 1;
            if (customers[i].balance - balance < 100)
            {
                printf("The balance is insufficent for specified Withdrawal\n");
            }
            else
            {
                printf("Withdrawal Successful\n");
            }
            break;
        }
    }
    if (!accountfound)
    {
        printf("Account not found!\n");
    }
}

void balanceLessThan100(struct customer customers[])
{
    for (int i = 0; i < max_customers; i++)
    {
        if (customers[i].accNo == 0)
        {
            break; // Exit the loop if encountering an uninitialized customer
        }
        if (customers[i].balance < 100 && strlen(customers[i].name) > 0)
        {
            printf("Account Number: %lld\n", customers[i].accNo);
            printf("Name: %s\n", customers[i].name);
        }
    }
}
