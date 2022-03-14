#ifndef UTILITIES_H
#define UTILITIES_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <iomanip>
using namespace std;



void gotoxy(short x, short y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

void debugger(vector<Step> tryValidSteps,Step curStep,ChessBoard board,int moveCount){
    gotoxy(0, board.size+2);
    cout << "                    ";
    gotoxy(0, board.size+2);
    cout << board(curStep) << endl;
    cout << tryValidSteps.size() << endl;
    cout << moveCount << endl;
}



#endif