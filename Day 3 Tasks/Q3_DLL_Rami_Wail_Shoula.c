//Q3_DLL_Rami_Wail_Shoula.c
//Q3: Implement all functions on double linked list of Employees

//#includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ITI.h"

//node to handle employee DLL list entries
struct node* createnode(struct node*);
void display(struct node*);
void search(struct node*);

struct node
{
    char name[10], des[10];
    int age;
    float salary;
    struct node* ptr;
};

//driving shit
int main()
{
    struct node* head;
    int b, i;

    head = NULL;

    while (1)
    {

        printf("\nEnter the value\n1-> to enter the employee details\n2->to display the results\n3->to search an element\n");
        scanf_s("%d", &b);

        switch (b)
        {
        case (1): printf("\nEnter the number of employee details you would like to enter\n");
            scanf_s("%d", &i);
            while (i > 0)
            {
                head = createnode(head);
                i--;
            }
            break;

        case (2): display(head);
            break;

        case (3): search(head);
            break;
        }
    }
}


void display(struct node* head)
{
    if (head == NULL)
    {
        printf("\nThe node is yet to be displayed \n");
    }

    else
    {
        while (head != NULL)
        {
            printf("\nThe name of the employee is %s\n", head->name);
            printf("\nThe designation of the employee is %s\n", head->des);



            printf("\nThe salary of the employee is %f\n", head->salary);



            printf("\nThe age of the employee is %d\n", head->age);

            head = head->ptr;

        }

    }
}

struct node* createnode(struct node* head)
{

    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));

    printf("\nEnter the employee name \n");
    scanf_s("%s", newnode->name,100);
    printf("\nEnter the employee's designation \n");
    scanf_s("%s", newnode->des,100);
    printf("\nEnter the salary of the employee \n");
    scanf_s("%f", &newnode->salary);
    printf("\nEnter the age of the employee\n");
    scanf_s("%d", &newnode->age);

    if (newnode == NULL)
    {
        printf("\n Enter the newnode \n");
        newnode->ptr = NULL;
    }

    else
    {
        newnode->ptr = head;

    }
    return newnode;
}


void search(struct node* head)
{
    char ch[10];

    printf("\nEnter the search string\n");

    scanf_s("%s", ch,100);


    while (head != NULL)
    {
        if (strcmp(ch, head->des) == 0)
        {
            printf("\nThe element is matched\n");
            printf("\nThe salary of the designated member is %f\n", head->salary);

        }

        else {
            printf("\nThe element is not matched\n");
        }
        head = head->ptr;
    }
}