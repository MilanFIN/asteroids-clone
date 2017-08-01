#include "projectile.h"
#include "math.h"
#define PI 3.14159265

Projectile::Projectile(int x, int y, int angle_)
{
    setPixmap(QPixmap("projectile.png"));
    xlocation = x;
    ylocation = y;
    angle = angle_-90;

    setPos(xlocation, ylocation);
    setTransformOriginPoint(3, 5);
    setRotation(angle_);

}

void Projectile::move()
{
    xlocation += speed*cos(angle*PI/180);
    ylocation += speed*sin(angle*PI/180);
    setPos(xlocation, ylocation);
}



int Projectile::getx()
{
    return int(xlocation);
}

int Projectile::gety()
{
    return int(ylocation);
}
