#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "assert.h"
#define EMPTY 0
#define WHITE 2
#define BLACK 1
#define MAXN 15
#define MAXDEP 2
#define ONE 10
#define TWO 100
#define THREE 1000
#define FOUR 100000
#define FIVE 1000000
#define BLOCKED_ONE 1
#define BLOCKED_TWO 10
#define BLOCKED_THREE 100
#define BLCOKED_FOUR 1000
class ChessBoard
{
private:
        std::vector<std::vector<int> >Board;//0 none 1 black 2 white
        int cnt[2];

    public:
        ChessBoard();
        ~ChessBoard();
        std::vector<std::vector<int> > ShowBoard(){return Board;}
        ChessBoard put(int x,int y,int col);
        bool canput(int x,int y);
        bool hasNeighber(int x,int y);
        void clear();
        void print();
        int CheckWin();
        int Score(int x,int y,int col);
        static int scr[2][6];

        static int dx[4];
        static int dy[4];
};




#endif // CHESSBOARD_H
