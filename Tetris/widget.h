#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <random>
#include <QTimer>
#include <QVector>
#include "box.h"
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
    bool IsLost=false;
    QVector<QVector<Box*>> goida;//основной список блоков
    bool firstmove=true;
    void move(); // движение вниз
    bool CheckForMovement(); // проверка на движ
    void CreateNewFigure(); // создание фигры
    void StopAllMovement(); // Полная остановка - когда коснлулся
    QTimer timer;
    void rotate(int ipivot, int jpivot, int i2, int j2); // замена двух элементов
    void moveleft(); // налева
    void moveright(); //направа
    void fullrotate();
    bool CheckForCollision();
    void Row();
    bool CheckForEnd();
    int score = 0;
    QVector<QVector<Box*>> NextFigure;

protected:
    //void mousePressEvent(QMouseEvent * e);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void tick();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
