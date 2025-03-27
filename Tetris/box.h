#ifndef BOX_H
#define BOX_H
#include <QColor>
class Box
{
public:
    Box(/*int x, int y,*/ bool IM, bool IC, QColor clr);
    Box();
    Box(Box* x);
    //int x;
    //int y;
    int size=40;
    bool IsMoving;
    bool IsColidable;
    QColor color;
};

#endif // BOX_H
