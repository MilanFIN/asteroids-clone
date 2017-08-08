#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>

class Asteroid : public QGraphicsPixmapItem
{
public:
    Asteroid(int size);
    Asteroid(int size, int x, int y, float angle_of_heading);
    void move();
    int getx();
    int gety();
    int size();
    float getAngle();
private:
    int size_;
    int speed;
    float angle;
    float xlocation;
    float ylocation;
};

#endif // ASTEROID_H
