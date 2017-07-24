#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>

class Asteroid : public QGraphicsPixmapItem
{
public:
    Asteroid(int size);
    void move();
    int getx();
    int gety();
private:
    int speed;
    float angle;
    float xlocation = 0;
    float ylocation = 0;
};

#endif // ASTEROID_H
