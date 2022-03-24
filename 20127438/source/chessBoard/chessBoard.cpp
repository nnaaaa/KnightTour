
#include "../step/step.h"
#include "chessBoard.h"
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
    
    return os;
}

void ChessBoard::writeFile(int x,int y,int m,int moveCount,double runningTime,string strategy){
    ofstream f("20127438_" + strategy + "_" + to_string(m) + "_" + to_string(x+1) + "_" + to_string(y+1) + ".txt");

    f << x + 1 << " "<< y + 1<<" "<< m<<endl;
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
