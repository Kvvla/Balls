#include "box.h"

Box::Box(/*int x, int y,*/ bool IM, bool IC, QColor clr) {
    /*this->x=x;
    this->y=y;*/
    IsMoving = IM;
    IsColidable = IC;
    color=clr;
}
Box::Box() {
}
Box::Box(Box* x) {
    /*this->x=x->x;
    this->x=x->y;*/
    this->IsMoving = x->IsMoving;
    this->IsColidable = x->IsColidable;
    this->color = x->color;
}
