#ifndef PROJECTILE_H
#define PROJECTILE_H


class Projectile : public QGraphicsPixmapItem
{
public:
    Projectile(int x, int y, int angle);
    void move();
private:
    int xlocation;
    int ylocation;
    int angle;
    int speed = 3;
};

#endif // PROJECTILE_H
