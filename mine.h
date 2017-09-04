#ifndef MINE_H
#define MINE_H

#include <QGraphicsPixmapItem>
#include "player.h"
#include <ctime>

class Mine : public QGraphicsPixmapItem
{
public:
    Mine();
    //creates the mine to the location of the player
    Mine(Player* player);
    //moves the item
    void move();
    //returns x coordinate in int
    int getx();
    //-||- for y
    int gety();
    //returns age of object in seconds
    int getAge();
private:
    float initSpeed = 1;
    float deceleration = 1.1;
    float xspeed;
    float yspeed;

    float xlocation;
    float ylocation;

    time_t initTime;
};

#endif // MINE_H
