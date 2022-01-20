//Q6_Queue_RamiWailShoula.c 

//#includes
#include <stdio.h>
#include"ITI.h"
#include <conio.h>
#include <stdlib.h>
#include "string.h"

//global variables
int QueuePosition = 1;
int keyPressed = 0;
char end;
char Arr_1[100] = "Want to add to Queue? \n";
char Arr_2[100] = "Want to retrieve from Queue? \n";
char Arr_3[100] = "Want to print Entire Queue? \n";
char Arr_4[100] = "Want to exit? (Press Esc)\n\n\n";
int qElement = 0;
int idx = 0;

//implemented linked list with node
struct Node
{
	int data;
	struct Node* next;
};

//add to queue iplementation
void AddQueue(struct Node** head_ref, int new_data) //add element to bottom of queue (FIFO)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

//retrieve from queue implementation
int RetrieveQueue(struct Node* head, int index)
{
	struct Node* current = head;
	int count = 0;
	while (current != NULL)
	{
		if (count == index)
			return(current->data);
		count++;
		current = current->next;
	}
}

//Print entire queue implementation
void PrintQueue(struct Node* head)
{
	if (head == NULL)
	{
		printf("NULL\n");
	}
	else
	{
		printf("%d\n", head->data);
		PrintQueue(head->next);
	}
}

//Menu selecting visual
void MenuSelect(int realPosition, int MenuSelectPosition)
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

//Menu implementation for queue program
void menu() {
	while (keyPressed != 13)
	{
		clrscr(); //ITI.h
		printf("\nQ6.\n");
		printf(":==>>Queue Menu Program<<==:\n\n");

		MenuSelect(1, QueuePosition);
		if (QueuePosition != 1)
			printf(Arr_1);
		else
			putsHighlighted(Arr_1);

		MenuSelect(2, QueuePosition);
		if (QueuePosition != 2)
			printf(Arr_2);
		else
			putsHighlighted(Arr_2);

		MenuSelect(3, QueuePosition);
		if (QueuePosition != 3)
			printf(Arr_3);
		else
			putsHighlighted(Arr_3);

		MenuSelect(4, QueuePosition);
		if (QueuePosition != 4)
			printf(Arr_4);
		else
			putsHighlighted(Arr_4);

		char key;
		key = getKey();
		switch (key)
		{
		case 80:
			if (QueuePosition != 4)
				QueuePosition++;
			continue;

		case 72:
			if (QueuePosition != 1)
				QueuePosition--;
			continue;
		case 71:
			QueuePosition = 1;
			continue;
		case 79:
			QueuePosition = 4;
			continue;
		case 13:
			return;
		case 27:
			QueuePosition = 4;
			return 0;
		default:
			QueuePosition = QueuePosition;
			continue;
		}
	}
}

//driving shit
void main()
{
	struct Node* head = NULL;
	do
	{
		menu();
		switch (QueuePosition)
		{
		case 1:
			clrscr(); //ITI.h
			printf("Kindly enter the Queue element: ");
			scanf_s("%d", &qElement);
			AddQueue(&head, qElement);
			printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
			end = getKey();
			continue;
		case 2:
			clrscr();
			printf("Kindly enter the index: ");
			scanf_s("%d", &idx);
			printf("Element at index %d is %d", idx, RetrieveQueue(head, idx - 1));
			printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
			end = getKey();
			continue;
		case 3:
			clrscr();
			PrintQueue(head);
			printf("\nKindly press 'y' to continue\n Press any Key To Exit\n");
			end = getKey();
			continue;
		case 4:
			clrscr();
			printf("Thank You! closing now...\n");
			return;
		}

	} while (end == 89 || end == 121);
}
