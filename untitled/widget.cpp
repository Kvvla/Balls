#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //timer.start(1000);
    //connect(&timer, SIGNAL(timeout()), this, SLOT(updateColor()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    //painter.drawEllipse(QPoint(this->width()/2,this->height()), this->width()/2, this->height());

    for(int i=0; i<8; i++){
        painter.setBrush(clrs[i]);
        painter.drawEllipse(QPoint(this->width()/2,this->height()), this->width()/2-(width()/16*i), this->height()-(height()/8*i));
    }
}

