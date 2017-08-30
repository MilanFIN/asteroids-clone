#include "mine.h"
#include <iostream>


#define PI 3.14159265

Mine::Mine()
{

}

Mine::Mine(Player *player)
{

    initTime = time(0);

    setPixmap(QPixmap("mine.png"));

    setPos(player->x(), player->y());
    xspeed = initSpeed*cos((player->rotation()+90)*PI/180);
    yspeed = initSpeed*sin((player->rotation()+90)*PI/180);
    xlocation = player->x();
    ylocation = player->y();

}

void Mine::move()
{
    xlocation += xspeed;
    ylocation += yspeed;
    xspeed = xspeed/deceleration;
    yspeed = yspeed/deceleration;

    setPos(xlocation, ylocation);

}

int Mine::getx()
{
    return (int)xlocation;
}

int Mine::gety()
{
    return (int)ylocation;
}

int Mine::getAge()
{
     return difftime( time(0), initTime);
}
