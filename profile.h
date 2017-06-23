#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <vector>
#include "chessboard.h"
class Profile
{
public:
    Profile();
    ~Profile();
    static QString User1;
    static QString User2;
    static int SecRemainUser1;
    static int SecRemainUser2;
    static int NumberofUser;
    static int Turns; // 1 for user1 2 for user2
    static int RetractTime1;
    static int RetractTime2;
    static std::vector<std::vector <int> > board;
    static int CursorX;
    static int CursorY;
    static ChessBoard B;
    static bool Start;
};

#endif // PROFILE_H
