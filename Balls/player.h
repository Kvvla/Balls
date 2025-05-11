#ifndef PLAYER_H
#define PLAYER_H
#include <QPoint>
#include <QColor>
#include "ball.h"
class player
{
public:
    player(int w, int h);
    int x;
    int y;
    int size;
    QColor color;
    QPoint point;
    bool CheckColision(ball* other);
};

#endif // PLAYER_H
