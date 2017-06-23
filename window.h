#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class Window;
}

class Window : public QDialog
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    //bool eventFilter(QObject *obj, QEvent *ev) override;
    ~Window();
protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    Ui::Window *ui;

public slots:
    void Count_Down();
private slots:
    void on_Pause_clicked();
    void on_Surrender_clicked();
    void on_Retract_clicked();
    void on_Drawn_clicked();
};

#endif // WINDOW_H
