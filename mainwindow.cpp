#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "profile.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Single_clicked()
{
    this->hide();

    PlayAskSingle->setWindowTitle("单人游戏模式");
    PlayAskSingle->setFixedSize(400,300);
    Profile::NumberofUser = 1;
    Profile::Turns = 1;
    PlayAskSingle->show();
    PlayAskSingle->exec();
    Profile::SecRemainUser1 = Profile::SecRemainUser2 = 600;


    PlayWindow->setWindowTitle("Single");
    PlayWindow->setFixedSize(800,600);
    PlayWindow->show();
    PlayWindow->exec();
    this->show();
}

void MainWindow::on_Double_clicked()
{
    this->hide();

    qDebug("test3");
    PlayAskDouble->setWindowTitle("双人游戏模式");
    PlayAskDouble->setFixedSize(400,300);
    Profile::NumberofUser = 2;
    PlayAskDouble->show();
    qDebug("test4");
    PlayAskDouble->exec();
    qDebug("test5");
    Profile::SecRemainUser1 = Profile::SecRemainUser2 = 600;

    PlayWindow->setWindowTitle("Double");
    PlayWindow->setFixedSize(800,600);
    PlayWindow->show();
    PlayWindow->exec();
    this->show();
}
