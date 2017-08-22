#ifndef HOMING_H
#define HOMING_H

#include <QGraphicsPixmapItem>
#include "player.h"


//objects that move towards the player
class Homing : public QGraphicsPixmapItem
{
public:
    //constructor, creates the item outside of the screen and targets the player
    Homing(Player* player);
    //moves the item
    void move(Player* player);
    //returns x coordinate in int
    int getx();
    //-||- for y
    int gety();


private:
    float xlocation;
    float ylocation;
    float angle;
    float accel;
    float xspeed;
    float yspeed;
};

#endif // HOMING_H
