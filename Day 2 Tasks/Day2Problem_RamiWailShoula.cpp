// Day2Problem_RamiWailShoula.cpp : This file contains the 'main' function. Program execution begins and ends there.
// C project for day 2 tasks  

//as much as I want to clean this code and remove comments I always keep all edit comments as the remind me how I started and my thought flow and how I finally got to the end, srry! :)

#include<stdio.h>
#include<stdlib.h>
#include<cmath>
//#include<iomanip>
#include"ITI.h"
#include <string.h>
#include<windows.h>
#include <conio.h>
const int empTotNo = 100; //max No. of employees in database
int looping_emps = 0; //looping over emps from start to end

struct employee
{
    char empname[30];
    int empindex;
}emp[empTotNo];
/*void empindexcounter() {    // function to give the full empindex counts
    for (int i = 0; i < empTotNo; i++) {
        emp[i].empindex = i;
    }
}
*/
int loopindex = 0;
int NoAdd = 0; //No of employees to add
struct employee* ptr; //ptr to handle memory allocation
//int count = 0;

void AddNewEmp() { //funct. to add new employee empname and increment empindex to nearest empty index (empindex is initially 0 for all empTotNo)
    printf("\nHow many employees to add?\n");
    scanf_s("\n%d", &NoAdd);
    printf("Pease add: %d employee records: \n", NoAdd);
    while (looping_emps < empTotNo) {   //looping over emp id's (no.'s)
        for (int i = 0; i < NoAdd; i++)
        {
            // Memory allocation for noOfRecords structures
            printf("\nEnter employee name: ");
            // ptr = (struct employee*)malloc();
     ///////////////////////////////////////////////////////////////////////////////
     //      scanf_s("\n %s", (ptr + i)->empname);
            scanf_s("%s", &emp[i].empname);
            //printf("\nemployee name: \n%s", emp[i].empname);
            //printf("\nemployee index: \n%d", emp[i].empindex);
            emp[i].empindex = loopindex; //save current index
            printf("\nemployee index: \n%d\n\n", emp[i].empindex);
            loopindex++; //increment index
            looping_emps++; //increment loop emps in for loop

            //printf("\nemployee index: \n%s", emp[i].empname);
            // 
            //scanf_s("\n %s", &emp[i].empname);
            // 
            //printf("\nemployee name: %s", emp[i].empname); //&emp[i].empname)
            //printf("\nEnter employee index:");
            //scanf_s("\n %d", &emp[i].empindex);
            //person* myperson = (person*)malloc(sizeof(person));
            employee* handle = (employee*)malloc(sizeof(struct employee)); //useless line for now (not used)
            //printf("\nemployee index: %d", emp[i].empindex);
            //printf("\n%d\n", sizeof(&emp));

        }
        break; //exiting while loop as input finished
    } 
    looping_emps = 0; //resetting loop emps
}
void AddEmpById() { //fuct. to add a single employee by Index (Overrite empty or current emp details)
    //Id index insert by userwith def. index 0
    //for (int i = 0; i < empTotNo;i++) {)
    printf("\nEnter The index of the employee you want to edit (add): ");
    scanf_s("%d", &loopindex);
    if (loopindex<0 || loopindex>empTotNo)
    {
        printf("\nThis is an invalid index! Cancelling operation.\n");
        //break;
    }
    else {
        //scanf_s("%d", &loopindex);
        printf("You have selected to edit employee with index: %d\n", loopindex);
        printf("Enter employee (new) name: ");
        scanf_s("%s", &emp[loopindex].empname);
        printf("\nEmployee with index (ID): %d , has (new) name: %s\n", loopindex , &emp[loopindex].empname);
    }      
    loopindex = 0; //resetting loop index
}
void Disp(int xy) { //funct. that takes int index and prints emp details 
    printf("\nEmployee with index (ID): %d , has name: %s\n", xy, &emp[xy].empname);
}
void DispNameLoL(int xy) { //funct. that takes int index and prints emp details (name only) 
    printf("\n%s\n", &emp[xy].empname);
}
void DispEmpById() { //Func. displays emps by ID (ends at second 0 ID found since ID's are initalized to 0 at start of program (I checked)
    //I start loop from index 1 to skip the true 0 index.
    int xy = 0;
    do
    {
        Disp(xy);
        xy++;
    } while (emp[xy].empindex!=0);
    Disp(xy); //handling missing index
}

void DispAllEmps() { //funct to display all employees (names only) // this function is redundant XD to disp()
    int xy = 0;
    printf("\nList of all employees: \n");
    do
    {
        DispNameLoL(xy);
        xy++;
    } while (emp[xy].empindex != 0);
    DispNameLoL(xy); //handling missing index
    printf("\n"); //yes the code (run) looking good is very important to me 
}

void quickmenu() //menu function for Q1
{
    //string menu[5]
    char menu[5][100] = { "Add new Employee",
     "Add Employee by Index",
     "Display Employee by index",
     "Display All Employees",
     "Exit" };

    int x = 0;
    int exitcase = 0;
    while (true) {
        system("cls"); //clears screen 

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //colouring handle
        printf("Q1: Main menu: \nPlease press 'Esc' to return to previous menu.\n\n");

        for (int i = 0; i < 5; i++) {
            if (i == x)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                //menu[i] ="ABC";
                printf("%s\n", menu[i]); //finally got it to work!!! yay!!!
                //cout << menu[i] << endl; //i used cout here bec. i was unable to print a string with printf function sadly
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                //cout << menu[i] << endl;
                printf("%s\n", menu[i]);
            }
        }

        while (true) {
            if (GetAsyncKeyState(VK_ESCAPE) != 0)
            {
                break;
            }
            if (GetAsyncKeyState(VK_UP) != 0) {
                x = x - 1;
                if (x == -1) {
                    x = 4;
                }
                break;
            }

            else if (GetAsyncKeyState(VK_DOWN) != 0) {
                x = x + 1;
                if (x == 5) {
                    x = 0;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_HOME) != 0) {
                x = 0;
                break;
            }

            else if (GetAsyncKeyState(VK_END) != 0) {
                x = 4;
                break;
            }

            else if (GetAsyncKeyState(VK_RETURN) != 0) { //enter key
                //system("cls");
                switch (x) // switch cases for menu
                {
                case 0: printf("\nYou selected: Add new Employee.\n");
                    AddNewEmp();
                    break;
                case 1: printf("\nYou selected: Add Employee by Index\n");
                    AddEmpById();
                    break;
                case 2: printf("\nYou selected: Display Employee by index\n");
                    DispEmpById();
                    break;
                case 3: printf("\nYou selected: Display All Employees\n");
                    DispAllEmps();
                    break;
                case 4: printf("\nYou selected: Exit, Program is shutting down now.\n");
                    exitcase = 1;
                    break;
                }
                system("pause"); //pauses screen awaiting user input
            }

        }
        if(exitcase == 1)   break; //ends quickmenu on exit
    }
}
/*struct details //I took this from my old code from uni (cpp) // I don't steal code!! I have all my cpp files in one folder and will show them if required!. //# you can't plagiarize from yourself!
{
    char name[30];
    int eid;
    int salary;
}emp[5];
int n, i, id, ch;
*/
void linemenu()  //same concept as quick menu // I use built in functions from wondows.h header for handles and highlighting (yes I also know u guys stole the gotoxy and highlight functions from windows.h header bec. I worked with it b4 in cpp course. xd no offense 
{
    char menu[10] = { 'x','x','x','x','x','x','x','x','x','x' }; //empty string to edit in!
    //printf("%d",sizeof(menu)); //check
    int x = 0; //line counter // will be x & y for multiline
    int exitcase = 0;
    while (true) {
        //system("cls"); //clears screen 
        //printf("\n"); //random endl
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //colouring handle (from windows.h header also same syntax as within ITI.h header
        for (int i = 0; i < 10; i++) { //yeah for loop once bec. one line // won't change logic from quickmenu //lots of redundant loops // max 10 
            if (i == x) //holding char
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                //menu[i] ="ABC";
                printf("%c", menu[i]); //finally got it to work!!! yay!!!
                //cout << menu[i] << endl; //i used cout here bec. i was unable to print a string with printf function sadly
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                //cout << menu[i] << endl;
                printf("%c", menu[i]);
            }
        }

        while (true) {
            if (GetAsyncKeyState(VK_ESCAPE) != 0)
            {
                break;
            }
            if (GetAsyncKeyState(VK_LEFT) != 0) {
                x = x - 1;
                if (x == -1) { //looping
                    x = 9;
                }
                //break;
            }

            else if (GetAsyncKeyState(VK_RIGHT) != 0) {
                x = x + 1;
                if (x == 9) { //looping
                    x = 0;
                }
                //break;
            }
            else if (GetAsyncKeyState(VK_HOME) != 0) {
                x = 0; //first char
                //break;
            }

            else if (GetAsyncKeyState(VK_END) != 0) {
                x = 9; //last char
                //break;
            }

            else if (GetAsyncKeyState(VK_RETURN) != 0) { //enter key //line editor mode
                //system("cls");
                //scanf_s("%c",menu[x]);
                //system("pause"); //pauses screen awaiting user input
            }

        }
        break;
        //if (exitcase == 1)   break; //ends quickmenu on exit
    }
}
void multiliemenu()
{

}
//still working on line editor
int main()
{
    //printf("%d\n", sizeof(&emp));
    int index = 0;
    //Q1
    system("pause"); //pauses screen awaiting user input
    system("cls");	 //clear screen
    quickmenu(); //call menu function
    //I honestly don't know why I should repeat all the last part usimg dynamic allocation so I might skip this (redundant task)
    //Q2

    //Q3 //Line editor
    //system("cls"); //clears screen 
    //printf("Q3: Line editor, Please enter the line up to 10 characters: \nPlease press 'Esc' key to Exit the line editor.\n\n");
    //linemenu();

    return 0;
}