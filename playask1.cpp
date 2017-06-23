#include "playask1.h"
#include "ui_playask1.h"
#include "profile.h"
#include <QMessageBox>
PlayAsk1::PlayAsk1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayAsk1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

PlayAsk1::~PlayAsk1()
{
    delete ui;
}

void PlayAsk1::on_Enter_clicked()
{
    if(ui->SingleUserName->text()!=""){
        Profile::User1 = ui->SingleUserName->text();

        this->hide();
        this->close();
    }
    else
        QMessageBox::warning(this,"Warning","或许你应该键入一个帅气的名字?",QMessageBox::Yes);

}
