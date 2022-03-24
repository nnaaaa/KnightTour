#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include "../step/step.h"
#include <string>

class Step;

class ChessBoard
{
private:
    int **board;

public:
    int size;
    ChessBoard(int);
    int &operator()(Step);
    friend std::ostream &operator<<(std::ostream &,ChessBoard);
    void writeFile(int,int,int,int,double,std::string);
};

#endif