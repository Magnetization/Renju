#include "playask2.h"
#include "ui_playask2.h"
#include "profile.h"
#include <QString>
#include <QMessageBox>
PlayAsk2::PlayAsk2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayAsk2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

PlayAsk2::~PlayAsk2()
{
    delete ui;
}

void PlayAsk2::on_Enter_clicked()
{
    QString User1_temp = ui->DoubleUserName1->text();
    QString User2_temp = ui->DoubleUserName2->text();
    if(User1_temp.compare("") && User2_temp.compare("") && User1_temp.compare(User2_temp)){
        Profile::User1 = User1_temp;
        Profile::User2 = User2_temp;

        this->hide();
        this->close();
    }
    else{
        QMessageBox::warning(this,"Warning","或许你应该键入一个帅气的名字?",QMessageBox::Yes);
    }
}
