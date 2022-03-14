#include <stdio.h>
#include <iostream>
#include <time.h>

#include "../step/step.h"
#include "../chessBoard/chessBoard.h"
using namespace std;

class Heuristic
{
public:
    bool adjacentMove(ChessBoard &board, Step &curStep)
    {
        Step nextStep, validNextStep;
        bool hasValidNextStep = false;
        int minDegree = board.size;

        srand(time(NULL));
        int randStarting = rand() % 8;
        for (int i = randStarting; i < randStarting + 8; ++i)
        {
            nextStep = trySteps[i % 8] + curStep;
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

    bool WarnsdorffHeuristic(int x, int y, int chessBoardSize, int &moveCount)
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
            if (!this->adjacentMove(board, curStep))
                return false;
            moveCount++;
        }

        if (!curStep.isReachBeginStep(firstStep))
            return false;

        finishClock = clock();
        timeCount = finishClock - startClock;
        
        board.writeFile(x, y, chessBoardSize, moveCount, timeCount,"heuristic");
        return true;
    }

    void KnightTour(int x, int y, int chessBoardSize)
    {
        int moveCount = 0;
        bool isSolved = this->WarnsdorffHeuristic(x, y, chessBoardSize, moveCount);
        while (!isSolved)
        {
            isSolved = this->WarnsdorffHeuristic(x, y, chessBoardSize, moveCount);
            if (isSolved)
                cout << "Done !";
        }
    }
};