#include "window.h"
#include "ui_window.h"
#include <QTimer>
#include <QTime>
#include "profile.h"
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
#include "ai.h"
Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Count_Down()));
    timer->start(1000);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

Window::~Window()
{
    delete ui;
}


std::pair<int,int> dfs(ChessBoard Board,int dep,int mycol,int nowcol)//pair(bestscore,bestplace)
{
    int Winner = Board.CheckWin();
    if (Winner)
    {
        if (Winner == nowcol)
            return std::make_pair(ChessBoard::scr[1][5]*10,0);
        else
            return std::make_pair(-ChessBoard::scr[1][5]*10,0);
    }
    int bestscore = -ChessBoard::scr[1][5]*10, bestplace;
    if (dep == 0)
        return std::make_pair(1,0);
    ChessBoard nextBoard;
    for (int i=0;i<MAXN;i++)
        for (int j=0;j<MAXN;j++)
        if (Board.canput(i,j) && Board.hasNeighber(i,j))
        {
            //printf("put %d %d %d\n",i,j,nowcol);
            //Board.print();
            nextBoard = Board.put(i,j,nowcol);
            int nowscore = nextBoard.Score(i,j,nowcol);
            if (dep > 0)
                nowscore -= dfs(nextBoard,dep-1,mycol,3-mycol).first;
            if (nowscore > bestscore)
            {
                bestscore = nowscore;
                bestplace = i*MAXN + j;
            }
            //if (dep == MAXDEP) printf("%d %d %d %d %d\n",i,j,nowscore,bestscore,bestplace);
        }
    return std::make_pair(bestscore,bestplace);
}


void Window::Count_Down(){
    QPixmap AI,Oppo,My;
    AI.load(":/new/image/Chenqi.jpg");
    Oppo.load(":/new/image/pdx.jpg");
    My.load(":/new/image/hmbb.jpg");
    if(Profile::NumberofUser== 1){
       ui->OppoName->setText("Competing With: AI");
       ui->OppoImg->setPixmap(AI);
       ui->OppoImg->setFixedSize(120,120);
       ui->OppoImg->show();
    }
    else if(Profile::NumberofUser ==2){
        QString Compete1 = "Competing With:";
        Compete1.append(Profile::User2);
        ui->OppoName->setText(Compete1);
        QString Compete2 = "Competing With:";
        Compete2.append(Profile::User1);
        ui->MyName->setText(Compete2);
        ui->MyImg->setPixmap(My);
        ui->MyImg->setFixedSize(120,120);
        ui->MyImg->show();
        ui->OppoImg->setPixmap(Oppo);
        ui->OppoImg->setFixedSize(120,120);
        ui->OppoImg->show();
    }
    //static int Profile::SecRemainUser1 = 600;
    //static int Profile::SecRemainUser2 = 600;
    if(Profile::Turns == 1){
        Profile::SecRemainUser1 --;
    }else if(Profile::Turns ==2){
        Profile::SecRemainUser2 --;
    }
    QString CountDown1 = "";
    if(Profile::SecRemainUser1 <600)
            CountDown1 = "0";
        int m1 = Profile::SecRemainUser1/60;
        int s1 = Profile::SecRemainUser1%60;
        if(s1>10){
            CountDown1.append(QString::number(m1));
            CountDown1.append(":");
            CountDown1.append(QString::number(s1));
        }else {
            CountDown1.append(QString::number(m1));
            CountDown1.append(":0");
            CountDown1.append(QString::number(s1));
        }
        ui->TimerMy->display(CountDown1);

        QString CountDown2 = "";
        if(Profile::SecRemainUser2 < 600)
           CountDown2 = "0";
        int m2 = Profile::SecRemainUser2/60;
        int s2 = Profile::SecRemainUser2%60;
        if(s2>10){
            CountDown2.append(QString::number(m2));
            CountDown2.append(":");
            CountDown2.append(QString::number(s2));
        }else {
            CountDown2.append(QString::number(m2));
            CountDown2.append(":0");
            CountDown2.append(QString::number(s2));
        }
        ui->TimerOppo->display(CountDown2);


}

void Window::on_Pause_clicked()
{
    int temp = Profile::Turns;
    Profile::Turns = 0;
    QMessageBox::warning(this,"Warning","Game stopped",QMessageBox::Yes);
    Profile::Turns = temp;
}

void Window::on_Surrender_clicked()
{
    int temp = Profile::Turns;
    Profile::Turns = 0;
    QString NameTemp;

    if(Profile::NumberofUser == 2){

        if(temp ==1){
            NameTemp = Profile::User1;
        }else if(temp ==2){
            NameTemp = Profile::User2;
        }
        NameTemp.append(", sure to surrender?");

        QMessageBox Surrender(QMessageBox::Warning,"question",NameTemp);
        Surrender.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        int choice = Surrender.exec();
        if(choice == QMessageBox::Yes){
            qDebug() << choice; // 增加投降接口
            for (int i = 0; i < 15; i++)
                for (int j = 0; j < 15; j++)
                    Profile::board[i][j] = 0;
            Profile::B.clear();
            Profile::CursorX = Profile::CursorY = 7;
            this->close();
        }else if(choice == QMessageBox::No){
            qDebug() << choice;
            Profile::Turns = temp;
        }
    }else if(Profile::NumberofUser == 1){
        NameTemp = Profile::User1;
        NameTemp.append(", sure to surrender?");
        QMessageBox Surrender(QMessageBox::Warning,"question",NameTemp);
        Surrender.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int choice = Surrender.exec();
        if(choice == QMessageBox::Yes){
            // 增加投降接口
            for (int i = 0; i < 15; i++)
                for (int j = 0; j < 15; j++)
                    Profile::board[i][j] = 0;
            Profile::B.clear();
            Profile::CursorX = Profile::CursorY = 7;
            this->close();
        }else if(choice == QMessageBox::No){
            Profile::Turns = temp;
        }
    }
}

void Window::on_Retract_clicked()
{/*
    int temp = Profile::Turns;
    Profile::Turns = 0;
    QString NameTemp;
    int TimesTemp;
    if(temp ==1){
        NameTemp = Profile::User1;
        TimesTemp = Profile::RetractTime1;
    }else if(temp ==2){
        NameTemp = Profile::User2;
        TimesTemp = Profile::RetractTime2;
    }
    qDebug() << TimesTemp;
    if(TimesTemp > 0 ){
        NameTemp.append(", sure to retract? Remain times is:");
        if(temp ==1){
            NameTemp.append(QString::number(Profile::RetractTime1,10));
        }else if(temp ==2){
            NameTemp.append(QString::number(Profile::RetractTime2,10));
        }
        QMessageBox Retract(QMessageBox::Warning,"question",NameTemp);
        Retract.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        int choice = Retract.exec();
        if(choice == QMessageBox::Yes){
            qDebug() << choice;
            if(temp ==1) Profile::RetractTime1-- ;
            else if(temp==2) Profile::RetractTime2-- ;
            qDebug() << Profile::RetractTime1;
        }else if(choice == QMessageBox::No){
            qDebug() << choice;
            Profile::Turns = temp;
        }
    }
    else {
       QMessageBox::warning(this,"Warning","You can't retract anymore",QMessageBox::Yes);
       Profile::Turns = temp;
    }*/
}


void Window::on_Drawn_clicked()
{
    if(Profile::NumberofUser == 1){
        QMessageBox::question(this,"question","Put an end to the game?",QMessageBox::Yes);
        QMessageBox::warning(this,"warning","ChenQi shuts down your request",QMessageBox::Yes);
    }else if(Profile::NumberofUser ==2){
        int temp = Profile::Turns;
        Profile::Turns = 0;
        QString NameTemp;
        if(temp == 1)
            NameTemp = Profile::User1;
        else if(temp ==2)
            NameTemp = Profile::User2;
        NameTemp.append(", Put an end to the game?");
        QMessageBox Drawn(QMessageBox::Question,"question",NameTemp);
        Drawn.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int choice = Drawn.exec();
        // user1 申请和棋 请求user2
        if(choice == QMessageBox::Yes){
            QMessageBox Request(QMessageBox::Question,"question","Do you agree to end this game",QMessageBox::Yes|QMessageBox::No);
            int Requestchoice = Request.exec();
            if(Requestchoice == QMessageBox::Yes){
                QMessageBox::question(this,"question","Your opponent accepted your request",QMessageBox::Yes);
                // GameOver 接口
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
            }else if(Requestchoice == QMessageBox::No){
                QMessageBox::question(this,"question","Your opponent shut down your request",QMessageBox::Yes);
                Profile::Turns = temp;
            }
        }else if(choice == QMessageBox::No){ // 放弃和棋 ，退出恢复状态
            Profile::Turns = temp;
        }
    }
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int i, j;
    p.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap));
    for (i = 0; i < 15; i++) {
        p.drawLine(50, 20 + i * 36, 554, 20 + i * 36);
        p.drawLine(50 + i * 36, 20, 50 + i * 36, 524);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (Profile::board[i][j] == 1) {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint(50 + i * 36, 20 + j * 36), 15, 15);
            } else if (Profile::board[i][j] == 2) {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint(50 + i * 36, 20 + j * 36), 15, 15);
            }
        }
    }

    i = Profile::CursorX;
    j = Profile::CursorY;
    QPoint points[3] = {
        QPoint(50+36*i-10, 20+36*j-5),
        QPoint(50+36*i-5, 20+36*j-5),
        QPoint(50+36*i-5, 20+36*j-10)
    };
    p.drawPolyline(points, 3);
    points[0] = QPoint(50+36*i+5, 20+36*j-10);
    points[1] = QPoint(50+36*i+5, 20+36*j-5);
    points[2] = QPoint(50+36*i+10, 20+36*j-5);
    p.drawPolyline(points, 3);
    points[0] = QPoint(50+36*i-5, 20+36*j+10);
    points[1] = QPoint(50+36*i-5, 20+36*j+5);
    points[2] = QPoint(50+36*i-10, 20+36*j+5);
    p.drawPolyline(points, 3);
    points[0] = QPoint(50+36*i+5, 20+36*j+10);
    points[1] = QPoint(50+36*i+5, 20+36*j+5);
    points[2] = QPoint(50+36*i+10, 20+36*j+5);
    p.drawPolyline(points, 3);
}


void Window::mouseReleaseEvent(QMouseEvent *e)
{
    int x, y;

    if (e->x() >= 50-18 && e->x() < 554+18 && e->y() >= 20-18 && e->y() < 524+18) {
        x = (e->x() - 32) / 36;
        y = (e->y() - 2) / 36;
        if (Profile::board[x][y] == 0 && Profile::NumberofUser == 2) {
            Profile::board[x][y] = Profile::Turns;
            qDebug("before put");
            Profile::B = Profile::B.put(x, y, Profile::Turns);
            qDebug("after put");
            Profile::CursorX = x;
            Profile::CursorY = y;
            update();
            if (Profile::B.CheckWin()) {
                update();
                if (Profile::Turns == 1){
                    QMessageBox::information(this, "Player 1 Win", "Player 1 Win", QMessageBox::Ok);
                    for (int i = 0; i < 15; i++)
                        for (int j = 0; j < 15; j++)
                            Profile::board[i][j] = 0;
                    Profile::B.clear();
                    Profile::CursorX = Profile::CursorY = 7;
                    this->close();
                }
                else{
                    QMessageBox::information(this, "Player 2 Win", "Player 2 Win", QMessageBox::Ok);
                    for (int i = 0; i < 15; i++)
                        for (int j = 0; j < 15; j++)
                            Profile::board[i][j] = 0;
                    Profile::B.clear();
                    Profile::CursorX = Profile::CursorY = 7;
                    this->close();
                }
            }
            if (Profile::Turns == 1)
                Profile::Turns = 2;
            else
                Profile::Turns = 1;
        }
        else if (Profile::board[x][y] == 0 && Profile::NumberofUser == 1 && Profile::Turns == 1){
            Profile::board[x][y] = Profile::Turns;
            Profile::B = Profile::B.put(x, y, Profile::Turns);
            Profile::CursorX = x;
            Profile::CursorY = y;
            update();
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "You Win", "You Win", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
                return;
            }
            auto choose = dfs(Profile::B, MAXDEP, WHITE, WHITE);
            Profile::board[choose.second/MAXN][choose.second%MAXN] = WHITE;
            Profile::B = Profile::B.put(choose.second/MAXN, choose.second%MAXN, WHITE);
            Profile::CursorX = choose.second/MAXN;
            Profile::CursorY = choose.second%MAXN;
            update();
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "Lose", "Lose", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                qDebug("upda");
                this->close();
                return;
            }
        }
    }
    update();
}

void Window::keyPressEvent(QKeyEvent *e) {
    //left
    if (Profile::CursorX - 1 >= 0){
        if (e->key()==Qt::Key_A && Profile::Turns == 1)
            Profile::CursorX--;
        if (e->key()==Qt::Key_J && Profile::Turns == 2)
            Profile::CursorX--;
    }
    //right
    if (Profile::CursorX + 1 < 15){
        if (e->key()==Qt::Key_D && Profile::Turns == 1)
            Profile::CursorX++;
        if (e->key()==Qt::Key_L && Profile::Turns == 2)
            Profile::CursorX++;
    }
    //up
    if (Profile::CursorY - 1 >= 0){
        if (e->key()==Qt::Key_W && Profile::Turns == 1)
            Profile::CursorY--;
        if (e->key()==Qt::Key_I && Profile::Turns == 2)
            Profile::CursorY--;
    }
    //down
    if (Profile::CursorY + 1 < 15){
        if (e->key()==Qt::Key_S && Profile::Turns == 1)
            Profile::CursorY++;
        if (e->key()==Qt::Key_K && Profile::Turns == 2)
            Profile::CursorY++;
    }
    //OK
    if (e->key()==Qt::Key_F && Profile::Turns == 1){
        Profile::board[Profile::CursorX][Profile::CursorY] = Profile::Turns;
        Profile::B = Profile::B.put(Profile::CursorX, Profile::CursorY, Profile::Turns);
        if (Profile::NumberofUser == 2){
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "Player 1 Win", "Player 1 Win", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
                return;
            }
            Profile::Turns = 2;
        }
        else if (Profile::NumberofUser == 1){
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "You Win", "You Win", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
                return;
            }
            auto choose = dfs(Profile::B, MAXDEP, WHITE, WHITE);
            Profile::board[choose.second/MAXN][choose.second%MAXN] = WHITE;
            Profile::B = Profile::B.put(choose.second/MAXN, choose.second%MAXN, WHITE);
            Profile::CursorX = choose.second/MAXN;
            Profile::CursorY = choose.second%MAXN;
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "You Lose", "You Lose", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
                return;
            }
        }
    }
    if (e->key()==Qt::Key_H && Profile::Turns == 2){
        Profile::board[Profile::CursorX][Profile::CursorY] = Profile::Turns;
        Profile::B = Profile::B.put(Profile::CursorX, Profile::CursorY, Profile::Turns);
        if (Profile::NumberofUser == 2){
            if (Profile::B.CheckWin()) {
                update();
                QMessageBox::information(this, "Player 2 Win", "Player 2 Win", QMessageBox::Ok);
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++)
                        Profile::board[i][j] = 0;
                Profile::B.clear();
                Profile::CursorX = Profile::CursorY = 7;
                this->close();
                return;
            }
            Profile::Turns = 1;
        }
    }
    update();
}
