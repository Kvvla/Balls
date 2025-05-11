#include "player.h"

player::player(int w, int h) {
    size = 20 + rand()%10;

    color = QColor::fromRgb(rand()%256, rand()%256, rand()%256);
    x=rand()%(w-2*size)+size;
    y=rand()%(h-2*size)+size;
    point=QPoint::QPoint(x, y);
}
bool player::CheckColision(ball *other){
    //Если коснулся сверху
    int x2=other->GetX();
    int y2=other->GetY();
    int r=other->GetSize();
    if (y-y2<r && y2<y && x2>x && x2<x+size){
        return true;
        //слева
    } else if ( x-x2<r && x2<x && y2>y && y2<y+size){
        return true;
        //снизу
    } else if (x2>x && x2<x+size && y2-(y+size)<r && y2>y+size){
        return true;
    } else if (y2>y && y2<y+size && x2-(x+size)<r && x2>x+size){
        return true;
    }
    else return false;
}
