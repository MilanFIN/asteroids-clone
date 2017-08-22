#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>

//objects that act as asteroids
class Asteroid : public QGraphicsPixmapItem
{
public:
    //creates asteroid at random place outside of play-area, moves to random direction
    //size: size of the asteroid (0-1)
    Asteroid(int size);
    //same as last, except location and direction aren't random
    //x,y: coordinates
    //angle_of_heading: direction that the asteroid is headed to, counter clockwise from parallel
    Asteroid(int size, int x, int y, float angle_of_heading);
    //moves the asteroid
    void move();
    //returns x coordinate in int
    int getx();
    //returns y coordinate
    int gety();
    //returns size of asteroid
    int size();
    //returns angle of direction
    float getAngle();
private:
    int size_;
    int speed;
    float angle;
    float xlocation;
    float ylocation;
};

#endif // ASTEROID_H
