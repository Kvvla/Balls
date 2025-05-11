#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lcdNumber->hide();

    balls.resize(NUM);
    //for(int i=0; i<NUM; i++){
        //balls[i]=new ball(width(), height() );
    //}
    //play=new player(width(), height() );


    connect(&ticktimer, SIGNAL(timeout()), this, SLOT(Tick()));
    connect(&secTimer, SIGNAL(timeout()), this, SLOT(AddSecond()));

}

Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
        case Qt::Key_A:
            play->x-=10;
            if (play->x<0) play->x+=10;
            play->point.setX(play->x);

            break;
        case Qt::Key_W:
            play->y-=10;
            if (play->y<0) play->y+=10;
            play->point.setY(play->y);

            break;
        case Qt::Key_S:
            play->y+=10;
            if (play->y>580) play->y-=10;
            play->point.setY(play->y);

            break;
        case Qt::Key_D:
            play->x+=10;
            if (play->x>580) play->x-=10;
            play->point.setY(play->x);

            break;
    }
}

void Widget::on_play_button_clicked()
{
    ui->lcdNumber->show();
    ui->play_button->hide();
    ui->exit_button->hide();
    ticktimer.start(30);
    secTimer.start(1000);
    TickStart=true;

    for(int i=0; i<NUM; i++){
        balls[i]=new ball(width(), height() );
    }
    play=new player(width(), height() );

}


void Widget::on_exit_button_clicked()
{
    this->close();
}

void Widget::Tick(){
    for (int i = 0; i<NUM; i++){
        balls[i]->move(width(), height());
        if(play->CheckColision(balls[i])) {
            //конец игры
            secTimer.stop();
            ticktimer.stop();
            TickStart=false;
            QMessageBox::warning(this, "Balls", "Игра огончена! Ваш результат "+QString::number(sec)+" секунд.");
            sec=0;
            ui->exit_button->show();
            ui->play_button->show();
            ui->lcdNumber->hide();
            for (int i=0; i<NUM; i++){
                delete balls[i];
            }
            delete play;
        }
        for (int j=0; j<NUM; j++){
            balls[i]->CheckColision(balls[j]);
        }
    }
    this->repaint();


}
void Widget::AddSecond(){
    sec++;
    ui->lcdNumber->display(sec);
}

void Widget::paintEvent(QPaintEvent *event){
    if (!TickStart) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    painter.setBrush(play->color);
    painter.drawRect(play->x, play->y, play->size, play->size);
    for (int i=0; i<NUM; i++){

        painter.setBrush(QBrush(balls[i]->GetColor()));

        painter.drawImage(balls[i]->GetX()-(balls[i]->GetSize()/2), balls[i]->GetY()-(balls[i]->GetSize()/2), QImage(":/new/rx/rx/Okhlobistynvkaemochke.png").scaled(2*balls[i]->GetSize(), 2*balls[i]->GetSize()));
    }
}
