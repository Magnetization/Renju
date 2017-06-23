#include "chessboard.h"
#include <QDebug>
std::vector<std::vector<int> > EmptyBoard;
int ChessBoard::scr[2][6] = {{0,1,10,100,10000,1000000},{0,10,100,1000,100000,1000000}};

int ChessBoard::dx[4] = {0,1,1,1};
int ChessBoard::dy[4] = {1,-1,0,1};//4 dirs

int calc(int count,int block,int empty)
{
    if (empty <= 0)
    {
        if (count >= 5) return ChessBoard::scr[1][5];
        if (block == 0)
            return ChessBoard::scr[1][count];
        if (block == 1)
            return ChessBoard::scr[0][count];
    }
    else if (empty == 1 || empty == count - 1)
    {
        if (count >= 6)
            return ChessBoard::scr[1][5];
        if (block == 0)
        {
            switch(count)
            {
                case 2:return ChessBoard::scr[1][2]/2;
                case 3:return ChessBoard::scr[1][3];
                case 4:return ChessBoard::scr[0][4];
                case 5:return ChessBoard::scr[1][4];
            }
        }
        if (block == 1)
        {
            if (count == 5)
                return ChessBoard::scr[0][4];
            else
                return ChessBoard::scr[0][count];
        }
    }
    else if(empty == 2 || empty == count-2)
    {
        if(count >= 7)
            return ChessBoard::scr[1][5];
        if(block == 0)
        {
            switch(count)
            {
                case 3: return ChessBoard::scr[1][3];
                case 4:
                case 5: return ChessBoard::scr[0][4];
                case 6: return ChessBoard::scr[1][4];
            }
        }

        if(block == 1)
        {
            switch(count)
            {
                case 3: return ChessBoard::scr[0][3];
                case 4: return ChessBoard::scr[0][4];
                case 5: return ChessBoard::scr[0][4];
                case 6: return ChessBoard::scr[1][4];
            }
        }

        if(block == 2)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6: return ChessBoard::scr[0][4];
            }
        }
    }
    else if(empty == 3 || empty == count-3)
    {
        if(count >= 8)
        {
            return ChessBoard::scr[1][5];
        }
        if(block == 0)
        {
            switch(count)
            {
                case 4:
                case 5: return ChessBoard::scr[1][3];
                case 6: return ChessBoard::scr[0][4];
                case 7: return ChessBoard::scr[1][4];
            }
        }

        if(block == 1)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6: return ChessBoard::scr[0][4];
                case 7: return ChessBoard::scr[1][4];
            }
        }

        if(block == 2)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6:
                case 7: return ChessBoard::scr[0][4];
            }
        }
    }
    else if(empty == 4 || empty == count-4)
    {
        if(count >= 9)
            return ChessBoard::scr[1][5];
        if(block == 0)
        {
            switch(count)
            {
                case 5:
                case 6:
                case 7:
                case 8: return ChessBoard::scr[1][4];
            }
        }

        if(block == 1)
        {
            switch(count)
            {
                case 4:
                case 5:
                case 6:
                case 7: return ChessBoard::scr[0][4];
                case 8: return ChessBoard::scr[1][4];
            }
        }

        if(block == 2)
        {
            switch(count)
            {
                case 5:
                case 6:
                case 7:
                case 8: return ChessBoard::scr[0][4];
            }
        }
    }
    else if(empty == 5 || empty == count-5)
    {
        return ChessBoard::scr[1][5];
    }

    return 0;
}



ChessBoard::ChessBoard()
{
    //qDebug("test");
    std::vector<int>tmp;
    for (int i=0;i<MAXN;i++)
    {
        tmp.clear();
        for (int j=0;j<MAXN;j++)tmp.push_back(0);
            Board.push_back(tmp);
    }
    cnt[0] = cnt[1] = 0; ////
    //qDebug("test2");
}

ChessBoard::~ChessBoard()
{
    EmptyBoard.clear();
    EmptyBoard.swap(Board);// A trick to release space of vector?
}

ChessBoard ChessBoard::put(int x,int y,int col)
{
    assert(Board[x][y] == 0);
    ChessBoard res;
    res.cnt[BLACK] = cnt[BLACK];
    res.cnt[WHITE] = cnt[WHITE];
    res.cnt[col]++;
    res.Board = Board;
    res.Board[x][y] = col;
    return res;
}

void ChessBoard::print()
{
    puts("");
    for (int i=0;i<MAXN;i++)
    {
        for (int j=0;j<MAXN;j++)
            qDebug("%c ",Board[i][j]);
            qDebug("\n");
    }
    puts("");
}

bool ChessBoard::canput(int x,int y)
{
    return Board[x][y] == EMPTY;
}

bool inBoard(int x,int y)
{
    return x>=0 && y>=0 && x<MAXN && y<MAXN;
}


bool ChessBoard::hasNeighber(int x,int y)//Whether a position is near to other chesses
{
    for (int dir = 0; dir < 4; dir++)
        for (int i=-2;i<=2;i++)
        {
            if (i==0) continue;
            int nx = x+i*dx[dir], ny = y+i*dy[dir];
            if (inBoard(nx,ny) && Board[nx][ny] != EMPTY)
                return true;
        }
    return false;
}


void ChessBoard::clear()
{
    cnt[0] = cnt[1] = 0;
    for (int i=0;i<MAXN;i++)
        for (int j=0;j<MAXN;j++)
            Board[i][j] = EMPTY;
}


int ChessBoard::CheckWin()//0 no one has won. else return winner color
{
    for (int i=0;i<MAXN;i++)
        for (int j=0;j<MAXN;j++)
        if (Board[i][j])
        {
            int col = Board[i][j];
            for (int dir=0;dir<4;dir++)
            {
                bool ok = true;
                for (int l=0;l<5;l++)
                {
                    int nx = i + dx[dir]*l, ny = j + dy[dir]*l;
                    //printf("Check %d %d %d\n",nx,ny,col);
                    if (nx >= MAXN || ny >= MAXN || nx < 0 || ny < 0 || Board[nx][ny] != col)
                    {
                        ok = false;
                        break;
                    //printf("%d %d is ok\n",nx,ny);
                    }
                }
                if (ok) return col;
            }
        }
    return 0;
}



int ChessBoard::Score(int x,int y,int col)
{
    assert(Board[x][y] == col);
    int res = 0;
    int count,block,scount,empty;
    int nx,ny;
    for (int dir = 0; dir < 4; dir++)
    {
        count = 1;
        block = 0;
        empty = -1;
        scount = 0;
        for (int i=1;i<=15;i++)
        {
            nx = x + i*dx[dir];
            ny = y + i*dy[dir];
            if (!inBoard(nx,ny))
            {
                block++;
                break;
            }
            int t = Board[nx][ny];
            if (t == EMPTY)
            {
                if (empty == -1 && inBoard(nx+dx[dir],ny+dy[dir]) && Board[nx+dx[dir]][ny+dy[dir]] == col)
                {
                    empty = count;
                    continue;
                }
                else break;
            }
            else if (t == col)
            {
                count++;
            }
            else
            {
                block++;
                break;
            }
        }
        for (int i=-1;i>=-15;i--)
        {
            nx = x + i*dx[dir];
            ny = y + i*dy[dir];
            if (!inBoard(nx,ny))
            {
                block++;
                break;
            }
            int t = Board[nx][ny];
            if (t == EMPTY)
            {
                if (empty == -1 && inBoard(nx-dx[dir],ny-dy[dir]) && Board[nx-dx[dir]][ny-dy[dir]] == col)
                {
                    empty = 0;
                    continue;
                }
                else break;
            }
            else if (t == col)
            {
                scount++;
                if (empty != -1)
                    empty++;
            }
            else
            {
                block++;
                break;
            }
        }
        count += scount;
        res += calc(count,block,empty);
    }
    return res;
}
