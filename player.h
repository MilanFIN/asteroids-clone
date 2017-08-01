#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include "math.h"


class Player : public QGraphicsPixmapItem
{
public:
    Player();
    void accelerate();
    void move();

private:
    int asd;
    float acceleration = 0.10;
    float drag = 0.01;
    float xspeed = 0;
    float yspeed = 0;
};

#endif // PLAYER_H
