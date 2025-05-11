#ifndef BALL_H
#define BALL_H
#include <QColor>
#include <QPoint>
class ball {
    public:
        ball(int w, int h);
        void move(int w, int h);
        int GetSize();
        QColor GetColor();
        int GetX();
        int GetY();
        QPoint point;
        void CheckColision(ball* other);
        int vx;
        int vy;

    private:
        int x;
        int y;

        QColor color;
        int size;
};

#endif // BALL_H
