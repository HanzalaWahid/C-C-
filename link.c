#include <stdio.h>
#include <stdlib.h>

struct node
{
    int Data;
    struct node *Link;
};

int main (){

struct node *head =malloc(sizeof(struct node));
struct node *second =malloc(sizeof(struct node));
struct node *third =malloc(sizeof(struct node));

head ->Data = 19;
head ->Link = second;
head ->Data = 24;
head ->Link = third;
head ->Data = 16;
head ->Link = NULL;




    return 0;
}
