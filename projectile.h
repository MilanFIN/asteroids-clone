#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>


class Projectile : public QGraphicsPixmapItem
{
public:
    Projectile(int x, int y, int angle_);
    void move();
    int getx();
    int gety();
private:
    int xlocation;
    int ylocation;
    int angle;
    int speed = 7;
};

#endif // PROJECTILE_H
