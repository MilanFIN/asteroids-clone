#include "player.h"
#include <iostream>


#define PI 3.14159265

Player::Player()
{

}

void Player::move()
{
    setPos(x()+ xspeed, y()+ yspeed);

    if (xspeed > 0){
        xspeed -= drag;
    }
    else if (xspeed < 0){
        xspeed += drag;
    }
    if (yspeed > 0){
        yspeed -= drag;
    }
    else if (yspeed < 0){
        yspeed += drag;
    }


    if (y() < -160){
        setPos(x(), 160);
    }
    if (y() > 160){
        setPos(x(), -160);
    }
    if (x() < -210){
        setPos(200, y());
    }
    if (x() > 210){
        setPos(-200, y());
    }


}

void Player::accelerate()
{
    xspeed += acceleration * std::sin(PI/180.00*rotation());
    if (xspeed > 10.0){
        xspeed = 10.0;
    }
    else if (xspeed < -10.0){
        xspeed = -10.0;
    }
    std::cout << xspeed << std::endl;

    yspeed -= acceleration * std::cos(PI/180.00*rotation());
    if (yspeed > 10.0){
        yspeed = 10.0;
    }
    else if (yspeed < -10.0){
        yspeed = -10.0;
    }
}
