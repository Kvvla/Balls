#include "ball.h"

ball::ball(int w, int h) {

    size = 20 + rand()%10;

    color = QColor::fromRgb(rand()%256, rand()%256, rand()%256);
    x=rand()%(w-2*size)+size;
    y=rand()%(h-2*size)+size;
    point=QPoint::QPoint(x, y);
    vx = 5 + rand()%5;
    vy = 5 + rand()%5;
    if (rand()%2==0) vx *= -1;
    if (rand()%2==0) vy *= -1;
}

void ball::move(int w, int h) {
    x+=vx;
    y+=vy;

    if (x<size/2 || x>(w-size)){
        vx=-vx;
        x+=vx;
    }
    if (y<size/2 || y>(h-size)){
        vy=-vy;
        y+=vy;
    }

    point.setX(x);
    point.setY(y);
}

int ball::GetSize(){
    return size;
}

QColor ball::GetColor(){
    return color;
}

int ball::GetX(){
    return x;
}

int ball::GetY(){
    return y;
}

void ball::CheckColision(ball *other){
    if (this==other) return;
    if ((other->GetX()-(x))*(other->GetX()-(x))+((other->GetY())-y)*((other->GetY())-y)<(size+(other->size))*(size+(other->size))){

        vx=-vx;
        vy=-vy;
        other->vx=-other->vx;
        other->vy=-other->vy;
    }
}
