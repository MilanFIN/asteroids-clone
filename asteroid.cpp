#include "asteroid.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265



Asteroid::Asteroid(int size)
{
    size_ = size;
    if (size == 0){
        setPixmap(QPixmap("0.png"));
    }

    if (size == 1){
        setPixmap(QPixmap("1.png"));
    }

    speed = (rand()%3)+1;


    int edge = (rand()%4)+1;
    //int edge = 1; //for testing only
    int xtarget;
    int ytarget;



    if (edge == 1){
        //spawn at left of screen in random location with semi random direction
        ylocation = (rand()%300)+1;
        xlocation = -250;
        ytarget = (rand()%300)+1;
        xtarget = 200;

        if (ylocation < 150){
            ylocation = -ylocation;
        } else {
            ylocation = ylocation -150;
        }

        if (ytarget < 150){
            ytarget = -ytarget;
        } else {
            ytarget = ytarget -150;
        }

        angle = atan(((float)ytarget - (float)ylocation)/float(450)) * 180/PI;

    }
    else if (edge == 2){
        //spawn at top of screen in random location with semi random direction
        ylocation = -200;
        xlocation = (rand()%400)+1;
        ytarget = 150;
        xtarget = (rand()%400)+1;

        if (xlocation < 200){
            xlocation = -xlocation;
        } else {
            xlocation = xlocation - 200;
        }
        if (xtarget < 200){
            xtarget = -xtarget;
        } else {
            xtarget = xtarget - 200;
        }

        angle = atan(((float)xtarget - (float)xlocation)/float(350)) * 180/PI - 90;
        //std::cout << angle << std::endl << xlocation << std::endl << xtarget << std::endl;

    }
    else if (edge == 3){
        //spawn at right of screen in random location with semi random direction
        ylocation = (rand()%300)+1;
        xlocation = 250;
        ytarget = (rand()%300)+1;
        xtarget = -200;

        if (ylocation < 150){
            ylocation = -ylocation;
        } else {
            ylocation = ylocation -150;
        }

        if (ytarget < 150){
            ytarget = -ytarget;
        } else {
            ytarget = ytarget -150;
        }

        angle = atan(((float)ytarget - (float)ylocation)/float(450)) * 180/PI + 180;
        //std::cout << angle << std::endl << ylocation << std::endl << ytarget << std::endl;

    }
    else if (edge == 4){
        //spawn at bottom of screen in random location with semi random direction
        ylocation = 200;
        xlocation = (rand()%400)+1;
        ytarget = -150;
        xtarget = (rand()%400)+1;

        if (xlocation < 200){
            xlocation = -xlocation;
        } else {
            xlocation = xlocation - 200;
        }
        if (xtarget < 200){
            xtarget = -xtarget;
        } else {
            xtarget = xtarget - 200;
        }

        angle = atan(((float)xtarget - (float)xlocation)/float(350)) * 180/PI + 180 + 90;//+90 is needed because angle is needed in relation to the x axis, this calculation is in relation to y
        //std::cout << angle << std::endl << xlocation << std::endl << xtarget << std::endl;

    }

    setPos((int)floor(xlocation), (int)floor(ylocation));


}

Asteroid::Asteroid(int size, int x, int y, float angle_of_heading)
{

    size_ = size;
    xlocation = float(x);
    ylocation = float(y);
    angle = angle_of_heading;
    speed = (rand()%3)+1;


    if (size == 0){
        setPixmap(QPixmap("0.png"));

    }

    if (size == 1){
        setPixmap(QPixmap("1.png"));

    }

    setPos((int)floor(xlocation), (int)floor(ylocation));

    std::cout << "xloc " << getx() << std::endl;


}

void Asteroid::move()
{
    xlocation += speed*cos(angle*PI/180);
    ylocation += speed*sin(angle*PI/180);
    setPos(xlocation, ylocation);
}

int Asteroid::getx()
{
    return int(xlocation);
}

int Asteroid::gety()
{
    return int(ylocation);
}

int Asteroid::size()
{
    return size_;
}

float Asteroid::getAngle()
{
    return angle;
}
