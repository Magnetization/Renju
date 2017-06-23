#include "profile.h"

Profile::Profile()
{

}
Profile::~Profile(){

}
QString Profile::User1 = NULL;
QString Profile::User2 = NULL;
int Profile::NumberofUser = 0;
int Profile::SecRemainUser1 = 600;
int Profile::SecRemainUser2 = 600;
int Profile::Turns = 1; // first set 1
int Profile::RetractTime1 = 3;
int Profile::RetractTime2 = 3;
std::vector<std::vector <int> > Profile::board(15, std::vector<int>(15, 0));
int Profile::CursorX = 7;
int Profile::CursorY = 7;
bool Profile::Start = false;
ChessBoard Profile::B;
