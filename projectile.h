#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>

//Projectile objects
class Projectile : public QGraphicsPixmapItem
{
public:
    //creates projectile
    //x,y: coordinates
    //angle_: direction of heading in degrees
    Projectile(int x, int y, int angle_);
    //moves the projectile to the direction of the angle
    void move();
    //returns x coordinate
    int getx();
    //returns y coordinate
    int gety();
private:
    int xlocation;
    int ylocation;
    int angle;
    int speed = 7;
};

#endif // PROJECTILE_H
