#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <random>
#include <QTimer>
#include <QVector>
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

private:
    Ui::Widget *ui;
    QTimer timer;
    QVector<QColor> clrs = {QColor(Qt::red), QColor(255,127,80), QColor(Qt::yellow), QColor(Qt::green), QColor(0,255,255), QColor(Qt::blue), QColor(Qt::magenta), QColor(Qt::white)};

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // WIDGET_H
