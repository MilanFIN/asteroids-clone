#include "hud.h"

Hud::Hud()
{

}

Hud::Hud(QGraphicsScene *scene_)
{
    scene = scene_;
    reset();
}

void Hud::reset()
{
    gameover = false;
    health = 5;
}

void Hud::hit()
{
    if (health <= 1){
        gameover = true;
    }
    else {
        --health;
    }
}

bool Hud::gameOver()
{
    return gameover;
}
