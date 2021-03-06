#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>
#include <algorithm>

#include "../step/step.cpp"
#include "../chessBoard/chessBoard.cpp"

using namespace std;
using namespace std::chrono;

class Backtrack
{
public:
    bool BacktrackingRecursive(Step curStep, Step beginStep, ChessBoard &board, unsigned long long &moveCount,clock_t startTime)
    {
        clock_t finishTime = clock();
        double timeCount = 1000 * (finishTime - startTime) / CLOCKS_PER_SEC;
        if (timeCount >= 3600000)
            return true;

        moveCount++;
        // stop condition is when current number equal 8*8-1 (63) if size is 8
        if (board(curStep) == board.size * board.size)
        {
            return true;
        }

        //vector<Step> tryValidNextSteps = curStep.getTryValidNextSteps(board);
        //Step::descendingDegreeOfStepsSort(tryValidNextSteps,board);
        //Step::descendingDistanceFromBeginSort(tryValidNextSteps, beginStep, board);
        srand(time(NULL));
        // int random = rand() % 8;
        for (int i = 0; i <  8; ++i)
        {
            Step nextStep = trySteps[i] + curStep;
            if (!nextStep.isValidStep(board))
                continue;
                
            board(nextStep) = board(curStep) + 1;

            if (BacktrackingRecursive(nextStep, beginStep, board, moveCount,startTime))
                return true;
            else
            {
                board(nextStep) = -1;
            }
        }
        return false;
    }

    void KnightTour(int x, int y, int chessBoardSize)
    {
        ChessBoard board(chessBoardSize);
        Step firstStep(x, y);
        firstStep.initStep(board);
        clock_t startClock, finishClock;
        double timeCount;
        unsigned long long moveCount = 0;
        startClock = clock();
        bool isSolved = BacktrackingRecursive(firstStep, firstStep, board, moveCount,startClock);
        finishClock = clock();
        timeCount = 1000 * (finishClock - startClock) / CLOCKS_PER_SEC;

        if (isSolved)
        {
            board.writeFile(x, y, chessBoardSize, moveCount, timeCount, "backtrack");
        }
    }
};