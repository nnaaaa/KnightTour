
#include "../step/step.h"
#include "chessBoard.h"
#include "../utilities.h"
#include <fstream>
#include <string>

ChessBoard::ChessBoard(int size) : size(size)
{
    this->board = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        this->board[i] = new int[size];
        for (int j = 0; j < size; ++j)
            this->board[i][j] = -1;
    }
}
int &ChessBoard::operator()(Step step){
    return this->board[ step .y][ step .x]; 
}

std::ostream &operator<<(std::ostream &os,ChessBoard board){
    gotoxy(0, 0);
    for (int i = 0; i < board.size;++i){
        for (int j = 0; j < board.size;++j){
            Step step(j, i);
            os <<setw(3)<< board(step)<<" ";
        }
        os << endl;
    }
    gotoxy(0, 20);
    return os;
}

void ChessBoard::writeFile(int x,int y,int m,int moveCount,double runningTime,string strategy){
    ofstream f("20127438_" + strategy + ".txt");

    f << x << " "<< y<<" "<< m<<endl;
    f << moveCount << endl;
    f << runningTime << endl;

    for (int i = 0; i < this->size;++i)
    {
        for (int j = 0; j < this->size;++j){
            f << this->board[i][j] <<" ";
        }
        f << endl;
    }
    f.close();
}
