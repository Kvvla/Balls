#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    goida.resize(20);
    this->setLayout(this->ui->gridLayout);
    for (int i=0; i<20; i++) {
        goida[i].resize(10);
        for (int j=0; j<10; j++){
            goida[i][j]=new Box(false, false, Qt::white);
        }
    }
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(300);
}

Widget::~Widget()
{
    delete ui;
}
bool Widget::CheckForEnd(){
    for (int i=0; i<10; i++){
        if (goida[0][i]->IsColidable){
            return true;
        }
    }
    return false;
}
void Widget::Row(){
    //проверяем, есть ли заполненный ряд
    bool lolkek=false;
    bool goidap=true;
    for (int i=0; i<20; i++){
        goidap=true;
        for (int j=0; j<10; j++){
            goidap=goidap&&goida[i][j]->IsColidable;
        }
        lolkek=lolkek||goidap;
    }
    //qDebug()<<"Maybe SMTH?";
    if (!lolkek) return;


    //У нас точно есть заполненный ряд

    while (lolkek){
        int sbdeleted;
        for (int i=0; i<20; i++){
            goidap=true;
            for (int j=0; j<10; j++){
                goidap=goidap&&goida[i][j]->IsColidable;
            }
            if (goidap) {
                sbdeleted=i;
                break;
            }

        }
        //мы нашли строчку, которую надо бы удалить
        for (int j=0; j<10; j++){
            goida[sbdeleted][j]= new Box(false, false, Qt::white);
        }

        //мы вроде бы ее удалили
        for(int i=sbdeleted-1; i>=0; i--){
            for (int j=0; j<10; j++){
                if (goida[i][j]->IsColidable){
                    goida[i+1][j]=new Box(goida[i][j]);
                    goida[i][j]=new Box(false, false, Qt::white);
                }
            }
        }
        //мы вроде бы все сместили
        score+=100;
        lolkek=false;
        goidap=true;
        for (int i=0; i<20; i++){
            goidap=true;
            for (int j=0; j<10; j++){
                goidap=goidap&&goida[i][j]->IsColidable;
            }
            lolkek=lolkek||goidap;
        }
        //Есть ли еще заполненные? Если да, то повторяем, если нет, то цикл прерывается.
    }

}
bool Widget::CheckForMovement(){
    for (int i=0; i<20; i++) {
        for (int j=0; j<10; j++){
            if (goida[i][j]->IsMoving){return true;}
        }
    }
    return false;
}
bool Widget::CheckForCollision(){
    for (int j=0; j<10; j++){
        if (goida[19][j]->IsMoving){return true;}
    }
    for (int i=0; i<19; i++) {
        for (int j=0; j<10; j++){
            if (goida[i][j]->IsMoving && goida[i+1][j]->IsColidable){return true;}
        }
    }
    return false;
}
void Widget::StopAllMovement(){
    //qDebug() << "Stiop!!! trgt";
    for (int i=0; i<20; i++) {
        for (int j=0; j<10; j++){
            if (goida[i][j]->IsMoving){
                goida[i][j]->IsMoving=false;
                goida[i][j]->IsColidable=true;
            }

        }
    }
}
void Widget::move(){
    //qDebug() << "Move trgt";
    score++;
    for (int i=19; i>=0; i--){
        for (int j=0; j<10; j++){

            if (goida[i][j]->IsMoving) {
                goida[i+1][j]=new Box(goida[i][j]);
                goida[i][j]=new Box(false, false, Qt::white);
            }

        }
    }
}
//С вот этой функцией ниже честно помог Дипсик
void Widget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:

        moveleft();
        break;
    case Qt::Key_Right:
        moveright();

        break;
    case Qt::Key_Up:

        fullrotate();
        break;
    case Qt::Key_Down:
        if (CheckForMovement()){
            if (!CheckForCollision()){
                move();
            } else StopAllMovement();
        }
    }
    update();
}
void Widget::fullrotate(){
    int minx=10, maxx=-1;
    int miny=20, maxy=-1;
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if (goida[i][j]->IsMoving){
                if (minx>j) minx=j;
                if (miny>i) miny=i;
                if (maxx<j) maxx=j;
                if (maxy<i) maxy=i;
            }
        }
    }
    int w=maxx-minx;
    int h=maxy-miny;
    if (w>h) h=w; else w=h;
    maxx=minx+w;
    maxy=miny+h;
    w++;
    h++;
    if (maxx<minx || maxy<miny) return;
    QVector<QVector<Box*>> antigoida;
    antigoida.resize(h);
    while (maxx>19){
        maxx--;
        minx--;
    }
    //записываем в антигойду
    if (maxx>9) return;
    for (int i=0; i<h; i++){
        antigoida[i].resize(w);
        for (int j=0; j<w; j++){
            antigoida[i][j]=new Box(goida[miny+i][minx+j]);
        }
    }
    //переворот антигойды
    for (int i=0;i<w/2;i++)
    {
        for (int j=i;j<w-i-1;j++)
        {
            Box* temp=new Box(antigoida[i][j]);
            antigoida[i][j]=new Box(antigoida[w-1-j][i]);
            antigoida[w-1-j][i]=new Box(antigoida[w-1-i][w-1-j]);
            antigoida[w-1-i][w-1-j]=new Box(antigoida[j][w-1-i]);
            antigoida[j][w-1-i]=new Box(temp);
        }
    }
    for (int i=0; i<h; i++){
        for (int j=0; j<w; j++){
            goida[miny+i][minx+j] = new Box(antigoida[i][j]);
        }
    }



}



void Widget::moveleft(){
    for(int i=0; i<20; i++){
        if (goida[i][0]->IsMoving) return;
    }
    bool CollisionCheck=false;
    for(int i=0; i<20; i++){
        for (int j=1;j<10; j++){

            CollisionCheck=goida[i][j]->IsMoving&&goida[i][j-1]->IsColidable||CollisionCheck;
        }
    }
    if (CollisionCheck) return;
    for(int i=0; i<20; i++){
        for (int j=1;j<10; j++){
            if (goida[i][j]->IsMoving&&!goida[i][j-1]->IsColidable&&!goida[i][j-1]->IsMoving){
                goida[i][j-1]=new Box(goida[i][j]);
                goida[i][j]=new Box(false, false, Qt::white);
            }
        }
    }
}

void Widget::moveright(){
    for(int i=0; i<20; i++){
        if (goida[i][9]->IsMoving) return;
    }
    bool CollisionCheck=false;
    for(int i=1; i<20; i++){
        for (int j=8;j>=0; j--){

            CollisionCheck=goida[i][j]->IsMoving&&goida[i][j+1]->IsColidable||CollisionCheck;
        }
    }
    if (CollisionCheck) return;
    for(int i=0; i<20; i++){
        for (int j=8;j>=0; j--){
            if (goida[i][j]->IsMoving&&!goida[i][j+1]->IsColidable&&!goida[i][j+1]->IsMoving){
                goida[i][j+1]=new Box(goida[i][j]);
                goida[i][j]=new Box(false, false, Qt::white);
            }
        }
    }
}
void Widget::tick(){
    this->ui->lcdNumber->display(score);
    if (CheckForEnd()){
        this->close();
        qDebug()<<"End of Game";
    }
    Row();
    if (CheckForMovement()){
        if (!CheckForCollision()){
            move();
        } else StopAllMovement();
    } else {
        CreateNewFigure();
    }
    this->repaint();


    //qDebug() << "slot is trigerred";
}

void Widget::CreateNewFigure(){
    QColor ThatOneColor= QColor::QColor(rand()%255, rand()%255, rand()%255);
    int clo=rand()%7;
    if (clo == 0) { //куб
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[1][5]=new Box(true, false, ThatOneColor);
        goida[1][6]=new Box(true, false, ThatOneColor);
    } else if (clo==1){ //Г
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[1][5]=new Box(true, false, ThatOneColor);
        goida[2][5]=new Box(true, false, ThatOneColor);
    } else if (clo==2){ //Г наоборот
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][4]=new Box(true, false, ThatOneColor);
        goida[1][5]=new Box(true, false, ThatOneColor);
        goida[2][5]=new Box(true, false, ThatOneColor);
    } else if (clo==3){ //s
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[1][6]=new Box(true, false, ThatOneColor);
        goida[1][7]=new Box(true, false, ThatOneColor);
    } else if (clo==4){ //z
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[1][5]=new Box(true, false, ThatOneColor);
        goida[1][4]=new Box(true, false, ThatOneColor);
    } else if (clo==5){ //ПАЛКА
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[0][7]=new Box(true, false, ThatOneColor);
        goida[0][8]=new Box(true, false, ThatOneColor);
    } else if (clo==6){ //T
        goida[0][5]=new Box(true, false, ThatOneColor);
        goida[0][6]=new Box(true, false, ThatOneColor);
        goida[1][6]=new Box(true, false, ThatOneColor);
        goida[0][7]=new Box(true, false, ThatOneColor);
    }

}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //qDebug() << "PaintTRGT";
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    for (int i=0; i<20; i++) {
        for (int j=0; j<10; j++){
            painter.setBrush(goida[i][j]->color);
            painter.drawRect(j*20, i*20, 20, 20);
        }
    }
}

void Widget::rotate(int ipivot, int jpivot, int i2, int j2){
    Box* zapas = goida[i2][j2];
    goida[i2][j2]=goida[ipivot+(j2-jpivot)][jpivot+(i2-ipivot)];
    goida[ipivot+(j2-jpivot)][jpivot+(i2-ipivot)]=zapas;
}
