#ifndef STEP_H
#define STEP_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "../chessBoard/chessBoard.h"
class ChessBoard;

class Step{
    public:
        int x, y;
    public:
        Step();
        Step(int,int);
        void initStep(ChessBoard &);
        bool isValidStep(ChessBoard &);
        Step operator+(Step);
        int operator-(Step);
        bool operator==(Step);
        int unvisitedAdjacencyCount(ChessBoard &);
        bool isReachBeginStep(Step);
        std::vector<Step> getTryValidNextSteps(ChessBoard &);
        static void descendingDegreeOfStepsSort(std::vector<Step> &,ChessBoard &);
        static void descendingDistanceFromBeginSort(std::vector<Step> &,Step,ChessBoard &);
};

Step trySteps[8] = {{1,2},{2,1},{-1,2},{1,-2},{-2,1},{2,-1},{-2,-1},{-1,-2}};
std::vector <Step> tryStepsVector = {{1,2},{2,1},{-1,2},{1,-2},{-2,1},{2,-1},{-2,-1},{-1,-2}};

#endif