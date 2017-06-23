#ifndef AI_H
#define AI_H
#include "chessboard.h"

class AI
{
public:
    AI();
    std::pair<int,int> dfs(ChessBoard Board,int dep,int mycol,int nowcol);
};

#endif // AI_H
