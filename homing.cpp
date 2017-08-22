#include "homing.h"
#include <iostream>

#define PI 3.14159265



Homing::Homing(Player* player)
{


    setPixmap(QPixmap("homing.png"));

    speed = (rand()%3)+1;


    int edge = (rand()%4)+1;



    if (edge == 0){
        //spawn at left of screen in random location
        ylocation = 0;
        xlocation = 0;
    }



    if (edge == 1){
        //spawn at left of screen in random location
        ylocation = (rand()%300)+1;
        xlocation = -250;
        if (ylocation < 150){
            ylocation = -ylocation;
        } else {
            ylocation = ylocation -150;
        }

    }
    else if (edge == 2){
        //spawn at top of screen
        ylocation = -200;
        xlocation = (rand()%400)+1;


        if (xlocation < 200){
            xlocation = -xlocation;
        } else {
            xlocation = xlocation - 200;
        }

    }
    else if (edge == 3){
        //spawn at right of screen
        ylocation = (rand()%300)+1;
        xlocation = 250;


        if (ylocation < 150){
            ylocation = -ylocation;
        } else {
            ylocation = ylocation -150;
        }

    }
    else if (edge == 4){
        //spawn at bottom of screen
        ylocation = 200;
        xlocation = (rand()%400)+1;

        if (xlocation < 200){
            xlocation = -xlocation;
        } else {
            xlocation = xlocation - 200;
        }

    }

    setPos((int)xlocation, (int)ylocation);


    if (player->x() > 0){
        angle = atan((ylocation - player->y())/(xlocation - player->x())) * 180/PI;

    }
    else if (player->x() < 0){
        angle = atan((ylocation - player->y())/(xlocation - player->x())) * 180/PI + 180;

    }
    std::cout << angle << std::endl;
    setTransformOriginPoint(20,20);
    setRotation(angle+90);

}

void Homing::move(Player* player)
{

    if (player->x() > xlocation){
        angle = atan((ylocation - player->y())/(xlocation - player->x())) * 180/PI;

    }
    else if (player->x() < ylocation){
        angle = atan((ylocation - player->y())/(xlocation - player->x())) * 180/PI + 180;

    }

    setRotation(angle+90);

    xlocation += speed*cos(angle*PI/180);

    ylocation += speed*sin(angle*PI/180);

    setPos(xlocation, ylocation);

}



int Homing::getx()
{
    return int(xlocation);
}

int Homing::gety()
{
    return int(ylocation);
}
