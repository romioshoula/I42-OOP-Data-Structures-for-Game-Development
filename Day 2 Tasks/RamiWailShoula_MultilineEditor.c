//RamiWailShoula_MultilineEditor.c

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#include"ITI.h"


void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}

//void gotoxy(int x, int y)
//{
  //  COORD coord = { 0,0 };
   // coord.X = x;
   // coord.Y = y;
   // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

int* LineEditor(int x, int y, int size, char minL, char maxL, char* str, int* length, int* command)
{
    //gotoxy(x,y);
    //puts("takes parameters correctly/n");
    int key = command[0];
    int prevCurr = command[1];

    int* retCommand = (int*)malloc(2 * sizeof(int));

    int x_copy = x;
    /*char*str;
    str = (char*)malloc(size);*/

    int last = x + (*length);
    x += (*length);

    int exit = 0;

    //puts("initializes correctly/n");

    char* st = str;
    char* end = str + (*length);
    char* curr = str;
    //puts("copies correctly/n");

    if (key == 9) //tab
    {
        curr = end;

    }
    else if (key == 72 || key == 80)
    {

        if (prevCurr < (*length))
        {
            curr = str + prevCurr;
            x -= (*length);
            x += prevCurr;
        }
        else {
            curr = end;
        }
    }

    char* bksp = curr;

    int b = 0;
    while (1 - exit) {
        _flushall();
        char c = getchar();
        char ch;
        switch (c)
        {
            //if null (Extended)
        case -32:
        case 0:
            //_flushall();
            ch = getchar();
            switch (ch)
            {
            case 75: // left
                if (st != curr)
                {
                    curr--;
                    x--;
                }
                break;
            case 77: // right
                if (curr != end)
                {
                    curr++;
                    x++;
                }
                break;
            case 71: // home
                curr = st;
                x = x_copy;
                break;
            case 79: // end
                curr = end;
                x = last;
                break;
            case 72:  // up
                retCommand[0] = 72; // ret key
                retCommand[1] = x - x_copy; //curr pos
                exit = 1;
                if (curr == end)
                    *curr = '\0';
                break;
            case 80:  // down
                retCommand[0] = 80; // ret key
                retCommand[1] = x - x_copy; //curr pos
                exit = 1;
                if (curr == end)
                    *curr = '\0';
                break;

            }
            break;
            //tab
        case 9:
            if (curr == end)
                *curr = '\0';

            exit = 1;
            retCommand[0] = 9; //ret key
            retCommand[1] = x - x_copy;//curr pos

            break;

        case 13: //enter
            *curr = '\0';
            exit = 1;
            retCommand[0] = 13; //ret key
            retCommand[1] = x - x_copy;//curr pos
            break;
            //backspace
        case 8:
            curr--;
            x--;
            end--;
            bksp = curr;
            (*length)--;

            while (bksp != end)
            {
                *bksp = *(bksp + 1);
                gotoxy(x + b, y);
                printf("%c", *bksp);
                b++;
                bksp++;
            }
            gotoxy(x + b, y);
            printf(" ");

            break;
            //real character
        default:
            if (c >= minL && c <= maxL)
            {


                gotoxy(x, y);
                printf("%c", c);
                //printf("%c",*curr);
                *curr = c;

                if (curr == end)
                {
                    end++;
                    last++;
                    (*length)++;
                }
                curr++;
                x++;
            }

            break;
        }

    }
    //  puts("here");

    //puts(str);

    return retCommand; //Contain Return Key, Current's Index
}

char** multipleLineEditor(int lines, int* sizes, int* xpos, int* ypos, char* r_start, char* r_end, int* length)
{
    system("cls");
    char** pad;
    pad = (char**)malloc(lines * sizeof(char*));
    for (int i = 0; i < lines; i++)
    {
        pad[i] = (char*)malloc(sizes[i] * sizeof(char));
    }


    //initialize length array
    for (int i = 0; i < lines; i++)
    {
        length[i] = 0;
    }
    //puts("creates 2d\n");
    int currLine = 0;

    int* cmd;
    cmd = (int*)malloc(2 * sizeof(char));
    cmd[0] = 0;
    cmd[1] = 0;

    int* editor;
    //puts("creates cmd");

    while (cmd[0] != 13)
    {
        editor = LineEditor(xpos[currLine], ypos[currLine], sizes[currLine], r_start[currLine], r_end[currLine], pad[currLine], &length[currLine], cmd);
        free(cmd);
        cmd = editor;
        if (cmd[0] == 72)
        {
            if (currLine > 0) currLine--;
        }
        else
        {
            if (currLine < lines - 1)
                currLine++;
        }

        //puts("passes");
        //'/*
       /* gotoxy(10,10);
        for(int i=0;i<lines;i++)
       {
           puts(pad[i]);
           //puts('\n');
       //
       }*/


    }

    system("cls");

    return pad;

}

int main()
{
    int lines;
    int* size;
    int* xpos;
    int* ypos;
    char* r_start;
    char* r_end;
    int* length;

    printf("Please Enter Maximum number of Lines:\n");
    scanf_s("%i", &lines);
    //printf("%i",lines);
    size = (int*)malloc(lines * sizeof(int));
    xpos = (int*)malloc(lines * sizeof(int));
    ypos = (int*)malloc(lines * sizeof(int));

    r_start = (char*)malloc(lines * sizeof(char));
    r_end = (char*)malloc(lines * sizeof(char));

    length = (int*)malloc(lines * sizeof(int));

    if (lines <= 0) { return 0; }


    printf("Enter Each Line's Data:\n");
    for (int i = 0; i < lines; i++) {
        printf("\nEnter Data of Line %i\n", i + 1);

        printf("Size: ");
        _flushall();
        scanf_s("%i", size + i);

        printf("X Position: ");
        _flushall();
        scanf_s("%i", xpos + i);

        printf("Y Position: ");
        _flushall();
        scanf_s("%i", ypos + i);

        printf("Range Start: ");
        _flushall();
        r_start[i] = getchar();
        //scanf_s("%c",r_start[i]);

        printf("\nRange End: ");
        _flushall();
        r_end[i] = getchar();
        //scanf_s("%c",r_end[i]);


    }
    /*  _flushall();
     system("cls");
     _flushall();*/

    char** pad;
    pad = multipleLineEditor(lines, size, xpos, ypos, r_start, r_end, length);

    //puts('/n');

    printf("The data you entered:\n\n");
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < length[i]; j++)
        {
            printf("%c", pad[i][j]);

        }
        if (length[i] > 0)
            printf("%c", '\n');
    }

    free(size);
    free(xpos);
    free(ypos);
    free(r_start);
    free(r_end);
    free(pad);

    return 0;
}