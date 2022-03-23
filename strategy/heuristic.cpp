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

    bool WarnsdorffHeuristic(int x, int y, int chessBoardSize, int &moveCount,vector<Step> &tryStepsQueue)
    {
        ChessBoard board(chessBoardSize);
        Step firstStep(x, y);
        firstStep.initStep(board);

        Step curStep = firstStep;
        clock_t startClock, finishClock;
        double timeCount;
        startClock = clock();
        
        for (int i = 0; i < board.size * board.size - 1; ++i)
        {
            if (i == 0){
                if (!this->adjacentMove(board, curStep,tryStepsQueue))
                    return false;
                tryStepsQueue.pop_back();
            }
            else{
                if (!this->adjacentMove(board, curStep,tryStepsVector))
                    return false;
            }
            moveCount++;
        }


        finishClock = clock();
        timeCount = 1000 * (finishClock - startClock) / CLOCKS_PER_SEC;
        
        board.writeFile(x, y, chessBoardSize, moveCount, timeCount,"heuristic");
        return true;
    }

    void KnightTour(int x, int y, int chessBoardSize)
    {
        int moveCount = 0;
        vector<Step> tryStepsQueue = {{-1, -2}, {-2, -1}, {2, -1}, {1, -2}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
        while(!this->WarnsdorffHeuristic(x, y, chessBoardSize, moveCount,tryStepsQueue))
        {
            if (tryStepsQueue.size() == 0)
                break;
        }
        
    }
};