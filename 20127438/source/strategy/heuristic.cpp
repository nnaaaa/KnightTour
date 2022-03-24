#include <stdio.h>
#include <iostream>
#include <time.h>

#include "../step/step.h"
#include "../chessBoard/chessBoard.h"
using namespace std;

class Heuristic
{
public:
    bool adjacentMove(ChessBoard &board, Step &curStep,vector<Step> &tryStepsQueue)
    {
        Step nextStep, validNextStep;
        bool hasValidNextStep = false;
        int minDegree = 8;

        for (int i = 0; i < tryStepsQueue.size(); ++i)
        {
            nextStep = tryStepsQueue[i] + curStep;
            if (!nextStep.isValidStep(board))
                continue;
            int curDegree = nextStep.unvisitedAdjacencyCount(board);
            if (board(nextStep) == -1 && curDegree <= minDegree)
            {
                hasValidNextStep = true;
                validNextStep = nextStep;
                minDegree = curDegree;
            }
        }

        if (!hasValidNextStep)
            return false;

        board(validNextStep) = board(curStep) + 1;
        curStep = validNextStep;
        return true;
    }

    bool WarnsdorffHeuristic(int x, int y, int chessBoardSize,ChessBoard *board, int &moveCount,vector<Step> &tryStepsQueue)
    {
        ChessBoard localBoard(*board);
        Step firstStep(x, y);
        firstStep.initStep(localBoard);

        Step curStep = firstStep;
        
        
        for (int i = 0; i < localBoard.size * localBoard.size - 1; ++i)
        {
            if (i == 0){
                if (!this->adjacentMove(localBoard, curStep,tryStepsQueue))
                    return false;
                tryStepsQueue.pop_back();
            }
            else{
                if (!this->adjacentMove(localBoard, curStep,tryStepsVector))
                    return false;
            }
            moveCount++;
        }


        
        
        
        return true;
    }

    void KnightTour(int x, int y, int chessBoardSize)
    {
        ChessBoard *board = new ChessBoard(chessBoardSize);
        int moveCount = 0;
        clock_t startClock, finishClock;
        double timeCount;
        startClock = clock();

        vector<Step> tryStepsQueue = {{-1, -2}, {-2, -1}, {2, -1}, {1, -2}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
        while(!this->WarnsdorffHeuristic(x, y, chessBoardSize,board, moveCount,tryStepsQueue))
        {
            if (tryStepsQueue.size() == 0)
                break;
        }

        finishClock = clock();
        timeCount = 1000 * (finishClock - startClock) / CLOCKS_PER_SEC;

        board->writeFile(x, y, chessBoardSize, moveCount, timeCount,"heuristic");
        
    }
};