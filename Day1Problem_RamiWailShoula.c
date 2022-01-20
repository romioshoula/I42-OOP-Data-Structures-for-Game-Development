// Day1Problem_RamiWailShoula.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//include headers
//#include<iostream>
//#include<cmath>
//#include<iomanip>
#include"ITI.h"
#include <stdio.h>
#include <string.h>
#include<windows.h>
#include <stdlib.h>

//using namespace std; //only for cpp

//func. that returns text user specific (void) for Q2
void get_ASCII_value(char c)
{
    printf("The ASCII value of %c = %d\n", c, c); //prints character and ascii equivalent no.
}

//func. that generates odd sized magic squares for Q3,4
void generateSquare(int n)
{
    //The magic constant of a normal magic square (odd n)
    //M = n(n^2+1)/2
    //ex: n=3 then M = 3*(3^2+1)/2 = 3*(9+1)/2 = 3*5 = 15

    int magicSquare[n][n]; //initialize 2D array (matrix) for magic square //works on any c compiler other than visual studio (legacy) compilers
    memset(magicSquare, 0, sizeof(magicSquare)); //set all entries in matrix to zeroes using built in func.'s memset and sizeof
    //position to place the initial 1 (relative to n size)
    int i = n / 2; //x loc (row)
    int j = n - 1; //y loc (column)
    // Use 3 conditions to individually place values in magic square //one for loop
    for (int loop = 1; loop <= n * n;)  //one loop over stretched entire 2D plane in one dimension for simplicity 
    { 
        if (i == -1 && j == n) // 3rd condition //resetting
        {
            j = n - 2;
            i = 0;
        }
        else {
            // 1st condition helper if next number exceeds square's right side // resetting columns
            if (j == n)
                j = 0;
            // 1st condition helper if next number exceeds square's top side // resetting rows
            if (i < 0)
                i = n - 1;
        }
        if (magicSquare[i][j]) // 2nd condition //resetting
        {
            j -= 2;   //resettig columns
            i++;
            continue; //increment row and continue
        }
        else
            magicSquare[i][j] = loop++; // set loop increment no.

        j++;
        i--; // 1st condition
    }
    // Print magic square
    printf("The Magic Square for n=%d:\nSum of "
        "each row or column %d:\n\n",
        n, n * (n * n + 1) / 2);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", magicSquare[i][j]); //"%3d "
        printf("\n");
    }
}

void quickmenu() //menu function for Q5
{
	//string menu[5]
    char menu[5][100] = { "Calculate the Sum and the Average of an array of integers",
     "Print Hello World",
     "Find the tallest and the shortest sentences of the user-input sentences",
     "Find the Treasure Game",
     "Exit" };

    int x = 0;

    while (true) {
        system("cls"); //clears screen 

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf( "Q5: Main menu: \n\n");

        for (int i = 0; i < 5; i++) {
            if (i == x)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                //menu[i] ="ABC";
                printf("%s\n",menu[i]); //finally got it to work!!! yay!!!
				//cout << menu[i] << endl; //i used cout here bec. i was unable to print a string with printf function sadly
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                //cout << menu[i] << endl;
                printf("%s\n",menu[i]);
            }
        }

        while (true) {
        	if (GetAsyncKeyState(VK_ESCAPE)!= 0) 
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
                case 0: printf( "\nYou selected: Calculate the Sum and the Average of an array of integers.\n"); 
                	break;   
                case 1: printf( "\nYou selected: Hello world\n"); 
                    break;
                case 2: printf( "\nYou selected: Find the tallest and the shortest sentences of the user-input sentences\n"); 
                    break;
                case 3: printf( "\nYou selected: Find the Treasure Game\n"); 
                    break;
                case 4: printf( "\nYou selected: Exit, Program is shutting down now.\n"); 
                    break;
                }
                system("pause"); //pauses screen awaiting user input
            }

        }

    }
}

//main function, I return int 0 to make sure main was successful 
int main()
{
	//int g=0;
	//int gg=0;
	//scanf("%d",&gg); //scanf("%c",&gg); //char is correct
	//	while(1)
	//	{
	//		g=_getch();	
	//		printf("%s","sdsgfjfg");
	//	}
    //Q1
    printf("Q1: \nHello World!\n");
    //std::cout << "Hello World!\n"; //cpp equivalent
    
    //Q2
    char c; //initialize character
    printf("Q2: \nPlease enter a character: "); //req. user input
    scanf("%c", &c); //user input
    //std::cin >> c; //cpp equivalent
    get_ASCII_value(c); //calling ascii conversion function

    //Q3 magic box 3x3 sum=15
    int n = 3; // Works only when n is odd
    printf("Q3: magic box 3x3 sum=15\n");
    generateSquare(n);  

    //Q4
    // Works only when n is odd
    printf("Q4: Please enter an odd number for magic box generation: "); //req. user input
    scanf("%d", &n); //user input
    // checking if no. is odd, true if num is not perfectly divisible by 2
    while(n % 2 == 0 || n<0 ) //if remainder when divided by 2 is 0 then it is even, request odd input
    {
    	printf("%d is even. or negative", n);
    	printf("\nkidly re-enter an 'odd' +ve number for magic box generation: ");
    	scanf("%d", &n); //user input
	}
    generateSquare(n);
    
    //Q5
    system("pause"); //pauses screen awaiting user input
    system("cls");	 //clear screen
	quickmenu(); //call meny function

    return 0;
}

//visual studio comments
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

