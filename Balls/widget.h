#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include "player.h"
#include "ball.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_play_button_clicked();
    void AddSecond();
    void Tick();
    void on_exit_button_clicked();

private:
    Ui::Widget *ui;
    bool TickStart=false;
    int sec=0;
    int NUM=5;

    QVector<ball*> balls;
    QTimer ticktimer;
    QTimer secTimer;
    player* play;
protected:
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent *event);

};
#endif // WIDGET_H
