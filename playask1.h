#ifndef PLAYASK1_H
#define PLAYASK1_H

#include <QDialog>

namespace Ui {
class PlayAsk1;
}

class PlayAsk1 : public QDialog
{
    Q_OBJECT

public:
    explicit PlayAsk1(QWidget *parent = 0);
    ~PlayAsk1();

private slots:
    void on_Enter_clicked();

private:
    Ui::PlayAsk1 *ui;
};

#endif // PLAYASK1_H
