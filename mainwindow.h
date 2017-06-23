#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "profile.h"
#include "window.h"
#include "playask1.h"
#include "playask2.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Single_clicked();

    void on_Double_clicked();

private:
    Ui::MainWindow *ui;
    Window *PlayWindow = new Window;
    PlayAsk1 *PlayAskSingle = new PlayAsk1;
    PlayAsk2 *PlayAskDouble = new PlayAsk2;
};

#endif // MAINWINDOW_H
