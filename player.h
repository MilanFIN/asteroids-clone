#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include "math.h"


class Player : public QGraphicsPixmapItem
{
public:
    //sets up player to the center of the screen
    Player();
    //adds speed to the direction the player is pointing at
    void accelerate();
    //moves the player to the direction the speed and angle specify
    void move();

private:
    int asd;
    float acceleration = 0.10;
    float drag = 0.01;
    float xspeed = 0;
    float yspeed = 0;
};

#endif // PLAYER_H
