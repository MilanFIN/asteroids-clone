#ifndef HOMING_H
#define HOMING_H

#include <QGraphicsPixmapItem>
#include "player.h"

class Homing : public QGraphicsPixmapItem
{
public:
    Homing(Player* player);
    void move(Player* player);
    int getx();
    int gety();

private:
    float xlocation;
    float ylocation;
    float angle;
    int accel;
    float xspeed;
    float yspeed;
};

#endif // HOMING_H
