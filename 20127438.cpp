#include <iostream>
#include <string>
#include "strategy/backtrack.cpp"
#include "strategy/heuristic.cpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int args, char **argv)
{
    Backtrack bt;
    Heuristic ht;

    bt.KnightTour(atoi(argv[2]) - 1, atoi(argv[4]) - 1, atoi(argv[6]));
    ht.KnightTour(atoi(argv[2]) - 1, atoi(argv[4]) - 1, atoi(argv[6]));

    system("pause");
    return 0;
}
