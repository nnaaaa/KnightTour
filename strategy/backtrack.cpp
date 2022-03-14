#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>
#include <algorithm>

#include "../step/step.cpp"
#include "../chessBoard/chessBoard.cpp"
#include "../utilities.h"

using namespace std;
using namespace std::chrono;

class Backtrack
{
public:
    bool BacktrackingRecursive(Step curStep, Step beginStep, ChessBoard &board, int &moveCount)
    {
        moveCount++;
        // stop condition is when current number equal 8*8-1 (63) if size is 8
        if (board(curStep) == board.size * board.size)
        {
            // if current isn't adjacent to beginStep, this tour can't complete
            if (!curStep.isReachBeginStep(beginStep))
                return false;
            return true;
        }

        vector<Step> tryValidNextSteps = curStep.getTryValidNextSteps(board);
        // Step::descendingDegreeOfStepsSort(tryValidNextSteps,board);
        Step::descendingDistanceFromBeginSort(tryValidNextSteps, beginStep, board);

        // debugger(tryValidNextSteps, curStep, board, moveCount);
        for (int i = 0; i < tryValidNextSteps.size(); ++i)
        {
            board(tryValidNextSteps[i]) = board(curStep) + 1;

            if (BacktrackingRecursive(tryValidNextSteps[i], beginStep, board, moveCount))
                return true;
            else
            {
                board(tryValidNextSteps[i]) = -1;
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
        int moveCount = 0;
        startClock = clock();
        bool isSolved = BacktrackingRecursive(firstStep, firstStep, board, moveCount);
        finishClock = clock();
        timeCount = finishClock - startClock;

        if (isSolved)
        {
            board.writeFile(x, y, chessBoardSize, moveCount, timeCount, "backtrack");
        }
    }
};