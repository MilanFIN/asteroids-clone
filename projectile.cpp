#include "projectile.h"
#include "math.h"
#define PI 3.14159265

Projectile::Projectile()
{
    //load pixmap here
}

void Projectile::move()
{
    xlocation += speed*cos(angle*PI/180);
    ylocation += speed*sin(angle*PI/180);
    setPos(xlocation, ylocation);
}
