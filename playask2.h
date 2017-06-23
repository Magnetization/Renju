#ifndef PLAYASK2_H
#define PLAYASK2_H

#include <QDialog>

namespace Ui {
class PlayAsk2;
}

class PlayAsk2 : public QDialog
{
    Q_OBJECT

public:
    explicit PlayAsk2(QWidget *parent = 0);
    ~PlayAsk2();

private slots:
    void on_Enter_clicked();

private:
    Ui::PlayAsk2 *ui;
};

#endif // PLAYASK2_H
