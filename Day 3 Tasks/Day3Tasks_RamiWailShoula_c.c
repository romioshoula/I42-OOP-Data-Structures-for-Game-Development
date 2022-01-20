//day3Tasks_RamiWailshoula_c.c 

//#includes
#include <stdio.h>
#include"ITI.h"
#include <conio.h>
#include <stdlib.h>
#include "string.h"

//Function Initialization/Declaration
void bubblesort();
void selectionsort();
//int *sort();
void binarysearch(int Arr[], int no);

//Q4 linked list struct
struct linkedList {
    char* value;
    struct linkedList* next;
};

struct Employee {
    char name[20];
}emp[10];

void addEmployee(index) {
    for (int i = 0; i < index; i++)
    {
        printf("Enter name of employee No. %d: \n", i + 1);
        scanf_s("%s", &emp[i].name, 100);
    }
}

int compare(struct linkedList* one, struct linkedList* two)
{
    return strcmp(one->value, two->value);
}

void add(struct linkedList** PtrPtr, char* value, int (*cmp)(struct linkedList* l, struct linkedList* r)) {
    struct linkedList* new;
    new = malloc(sizeof(*new));
    new->value = value;
    for (; *PtrPtr != NULL; PtrPtr = &(*PtrPtr)->next) {
        if (cmp(*PtrPtr, new) > 0) break;
    }
    new->next = *PtrPtr;
    * PtrPtr = new;
}

void display(struct linkedList* ptr) { //displaying linked list 

    for (; ptr != NULL; ptr = ptr->next) {
        printf("\n%s\n", ptr->value);
    }
}

//Q5 Stack (Push, Pop functions) using double linked list 
int element = 0;
int keyPressed = 0;
int Stackposition = 1;
char end;
char Arr_1[100] = "Want to Push an element?\n";
char Arr_2[100] = "Want to PoP an element?\n";
char Arr_3[100] = "Want to display elements?\n";
char Arr_4[100] = "Want to exit? (Press Esc)\n";

//implemented linked list with node
struct node
{
    int data;
    struct node* next;
    struct node* prev;
} *top;

//push in stack implementation
void push(int element)       //push (add) element to top of stack (FILO/LIFO)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node)); //dynamic memory allocation using malloc (c)
    if (!temp)
    {
        printf("Memory cannot be allocated!");
        return;
    }
    printf("Kindly Enter the element you want to push:\n");
    scanf_s("%d", &element);
    temp->data = element; //temp to handle data entries and switching
    if (top == NULL)    //Stack is LIFO (or FILO)
    {
        temp->next = NULL;
        temp->prev = NULL;
        top = temp;
    }
    else
    {
        top->next = temp;
        temp->prev = top;
        top = temp;
    }
}

//pop from stack implementation
int pop()           //pop (remove) element from top of stack (FILO/LIFO)
{
    if (top == NULL)
    {
        printf("You have successfully emptied the stack! No more entities available to pop :).\n");
        return 0;
    }
    if (top->next == NULL && top->prev == NULL) {
        int a = top->data;
        struct node* temp;
        temp = top;
        top = NULL;
        free(temp);
        return a;
    }
    struct node* temp;
    temp = top;
    top = top->prev;
    top->next = NULL;
    free(temp); //freeing temp value for next pop
}

//Displaying stack entities
void display_Stack()
{
    struct node* temp = top;
    if (temp == NULL) //case when user wants to display empty stack
    {
        printf("Stack is empty :/\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%d  ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

//Menu selecting visual
void MenuSelect(int realPosition, int MenuSelectPosition) //
{
    if (realPosition == MenuSelectPosition)
    {
        printf("Select Option :==>>");
    }
    else
    {
        printf("   ");
    }
}

//Menu implementation for stack program
void menu() {
    while (keyPressed != 13)
    {
        clrscr(); //ITI.h
        printf("\nQ5.\n");
        printf(":==>>Stack Menu Program<<==:\n\n");

        MenuSelect(1, Stackposition);
        if (Stackposition != 1)
            printf(Arr_1);
        else
            putsHighlighted(Arr_1); //ITI.h

        MenuSelect(2, Stackposition);
        if (Stackposition != 2)
            printf(Arr_2);
        else
            putsHighlighted(Arr_2);

        MenuSelect(3, Stackposition);
        if (Stackposition != 3)
            printf(Arr_3);
        else
            putsHighlighted(Arr_3);

        MenuSelect(4, Stackposition);
        if (Stackposition != 4)
            printf(Arr_4);
        else
            putsHighlighted(Arr_4);

        char key;
        key = getKey();
        switch (key)
        {
        case 80:
            if (Stackposition != 4)
                Stackposition++;
            continue;
        case 72:
            if (Stackposition != 1)
                Stackposition--;
            continue;
        case 71:
            Stackposition = 1;
            continue;
        case 79:
            Stackposition = 4;
            continue;
        case 13:
            return;
        case 27:
            Stackposition = 4;
            return 0;
        default:
            Stackposition = Stackposition;
            continue;
        }
    }
}

//main declaration || driving program (|| as in; or xd)
int main()
{
    //Q1: Bubble sort and Selection sort
    printf("Q1:\n");
    printf("Bubble sort algorith: \n");
    bubblesort();
    printf("\n");
    system("pause"); //pauses screen awaiting user continue input
    clrscr(); //"ITI.h"
    printf("Selection sort algorith: \n");
    selectionsort();
    printf("\n");
    system("pause");
    clrscr();

    //Q2: binar search algorithm
    printf("Q2:\n");
    printf("Binary Search algorith: \n");
    //int sortedarray[100];
    //int* ptr; //sorted array by means of pointer assertion
    //ptr =*sort();
    //printf("\n%d\n", sizeof(ptr));
    //system("pause");
    int array[100], no, c, d, position, swap;
    //unsorted array from user // this is sorted to aray[100]
    printf("Please Enter number of elements: ");
    scanf_s("%d", &no);
    printf("Enter %d integers\n", no);
    //sort algorithm placed here
    for (c = 0; c < no; c++)
        scanf_s("%d", &array[c]);
    for (c = 0; c < (no - 1); c++)
    {
        position = c;
        for (d = c + 1; d < no; d++)
        {
            if (array[position] > array[d])
                position = d;
        }
        if (position != c)
        {
            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
        }
    }
    printf("List after (selection) sorting:\n");
    for (c = 0; c < no; c++)
        printf("%d ", array[c]);
    printf("List has %d elements.\n", no);
    // Array is  sorted, run binary search
    int first, last, middle, search;
    //binarysearch(array[100],no);
    printf("\nEnter value to find in list: ");
    scanf_s("%d", &search);
    first = 0;
    last = no - 1;
    middle = (first + last) / 2;

    while (first <= last)
    {
        if (array[middle] < search)
            first = middle + 1;
        else if (array[middle] == search)
        {
            printf("%d found at location %d.\n", search, middle + 1);
            break;
        }
        else
            last = middle - 1;

        middle = (first + last) / 2;
    }
    if (first > last)
        printf("Not found! %d is not present in the list.\n", search);
    //end binary search
    system("pause"); //pauses screen
    clrscr(); //ITI.h

    //Q4:Insert employees sorted in linked list 
    printf("Q4:\n");
    struct linkedList* root = NULL;
    int i = 0;
    int s = 0;
    printf("Kindly Enter No. of Employees you want too add to list:\n");
    scanf_s("%d", &s);
    addEmployee(s);
    for (i; i < s; i++)
    {
        add(&root, emp[i].name, compare);
    }
    display(root);

    system("pause"); //pauses screen
    clrscr(); //ITI.h
    //Q5:Stack (Push, Pop functions) using double linked list
    //Stackposition = 1;
    do
    {
        menu();
        switch (Stackposition)
        {
        case 1:
            clrscr();
            push(element);
            printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
            end = getKey(); //ITI.h
            continue;
        case 2:
            clrscr();
            element = pop();
            printf("Successfully Poped (topmost) Element in stack!\n");
            printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
            end = getKey();
            continue;
        case 3:
            clrscr();
            display_Stack();
            printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
            end = getKey();
            continue;
        case 4:
            clrscr();
            printf("Kindly Note that Q3 (DLL Emlpoyees) and Q6 (Queue) Operations are in seperate .c\n\nThank You!\n");
            return;
        }
    } while (end == 89 || end == 121);
    return 0;
}

//Function bodies

//bubble sort algorithm
void bubblesort() {
    int array[100], no, c, d, swap;
    printf("Please Enter number of elements: ");
    scanf_s("%d", &no);
    printf("Enter %d integers: \n", no);
    for (c = 0; c < no; c++)
        scanf_s("%d", &array[c]);
    for (c = 0; c < (no - 1); c++)
    {
        for (d = 0; d < no - c - 1; d++)
        {
            if (array[d] > array[d + 1]) // For decreasing order use 
            {
                swap = array[d];
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }
    printf("Bubble sorted list in ascending order:\n");
    for (c = 0; c < no; c++)
        printf("%d ", array[c]);
}
//selection sort algorithm
void selectionsort() {
    int array[100], no, c, d, position, swap;
    printf("Please Enter number of elements: ");
    scanf_s("%d", &no);
    printf("Enter %d integers\n", no);
    for (c = 0; c < no; c++)
        scanf_s("%d", &array[c]);
    for (c = 0; c < (no - 1); c++)
    {
        position = c;
        for (d = c + 1; d < no; d++)
        {
            if (array[position] > array[d])
                position = d;
        }
        if (position != c)
        {
            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
        }
    }
    printf("Selection sorted list in ascending order:\n");
    for (c = 0; c < no; c++)
        printf("%d ", array[c]);
}
//sorting array using selection sort as it is faster than bubble sort
//not used as I couln't code returning an array via pointer easily
/*int* sort()
{
    int array[100], no, c, d, position, swap;
    //unsorted array from user // this is sorted to aray[100]
    printf("Please Enter number of elements: ");
    scanf_s("%d", &no);
    printf("Enter %d integers\n", no);
    for (c = 0; c < no; c++)
        scanf_s("%d", &array[c]);
    for (c = 0; c < (no - 1); c++)
    {
        position = c;
        for (d = c + 1; d < no; d++)
        {
            if (array[position] > array[d])
                position = d;
        }
        if (position != c)
        {
            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
        }
    }
    //printf("Selection sorted list in ascending order:\n");
    //for (c = 0; c < no; c++)
        //printf("%d ", array[c]);
    return array;
}
*/

//Binary Search algorithm
void binarysearch(int array[100], int no) //no is sizeof array
{
    int c, first, last, middle, search;
    printf("Enter value to find\n");
    scanf_s("%d", &search);

    no = sizeof(array);
    printf(" % d", no);
    system("pause");
    first = 0;
    last = no - 1;
    middle = (first + last) / 2;

    while (first <= last)
    {
        if (array[middle] < search)
            first = middle + 1;
        else if (array[middle] == search)
        {
            printf("%d found at location %d.\n", search, middle + 1);
            break;
        }
        else
            last = middle - 1;

        middle = (first + last) / 2;
    }
    if (first > last)
        printf("Not found! %d is not present in the list.\n", search);
}
