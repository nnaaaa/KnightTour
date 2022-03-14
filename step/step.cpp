#include <iostream>
#include "step.h"
#include <stdlib.h>
#include <vector>
#include "../chessBoard/chessBoard.h"
using namespace std;

Step::Step()
{
    x = 0;
    y = 0;
}
Step::Step(int x, int y) : x(x), y(y) {}
Step Step::operator+(Step after)
{
    Step before = *this;
    before.x += after.x;
    before.y += after.y;
    return before;
}
int Step::operator-(Step after)
{
    Step before = *this;
    int distance = abs(before.x - after.x) + abs(before.y - after.y);
    return distance;
}
bool Step::operator==(Step after)
{
    return this->x == after.x && this->y == after.y;
}

void Step::initStep(ChessBoard &board)
{
    board(*this) = 1;
}
bool Step::isValidStep(ChessBoard &board)
{
    return (this->x >= 0 && this->y >= 0 && this->x < board.size && this->y < board.size && board(*this) == -1);
}
int Step::unvisitedAdjacencyCount(ChessBoard &board)
{
    int count = 0;
    for (int i = 0; i < 8; ++i)
    {
        Step adjacentStep = *this + trySteps[i];
        if (adjacentStep.isValidStep(board) && board(adjacentStep) == -1)
            count++;
    }
    return count;
}
bool Step::isReachBeginStep(Step begin)
{
    for (int i = 0; i < 8; ++i)
    {
        if (*this + trySteps[i] == begin)
            return true;
    }
    return false;
}

std::vector<Step> Step::getTryValidNextSteps(ChessBoard &board)
{
    vector<Step> tryValidSteps;
    for (int i = 0; i < 8; ++i)
    {
        Step nextStep = *this + trySteps[i];
        if (nextStep.isValidStep(board))
            tryValidSteps.push_back(nextStep);
    }
    return tryValidSteps;
}

void Step::descendingDegreeOfStepsSort(std::vector<Step> &tryValidSteps, ChessBoard &board)
{
    for (int i = 0; i < tryValidSteps.size() - 1; ++i)
    {
        for (int j = i + 1; j < tryValidSteps.size(); ++j)
        {
            if (tryValidSteps[i].unvisitedAdjacencyCount(board) > tryValidSteps[j].unvisitedAdjacencyCount(board) || tryValidSteps[i].unvisitedAdjacencyCount(board) == 0)
            {
                Step temp = tryValidSteps[i];
                tryValidSteps[i] = tryValidSteps[j];
                tryValidSteps[j] = temp;
            }
        }
    }
}

void Step::descendingDistanceFromBeginSort(std::vector<Step> &tryValidSteps, Step begin, ChessBoard &board)
{
    for (int i = 0; i < tryValidSteps.size() - 1; ++i)
    {
        for (int j = i + 1; j < tryValidSteps.size(); ++j)
        {
            if (tryValidSteps[i].unvisitedAdjacencyCount(board) > tryValidSteps[j].unvisitedAdjacencyCount(board) || tryValidSteps[i].unvisitedAdjacencyCount(board) == 0)
            {
                Step temp = tryValidSteps[i];
                tryValidSteps[i] = tryValidSteps[j];
                tryValidSteps[j] = temp;
            }
        }
    }
}
