#include "hud.h"
#include <iostream>

Hud::Hud()
{

}

Hud::Hud(QGraphicsScene *scene_)
{

    hudBars.push_back(new QGraphicsPixmapItem);
    hudBars.push_back(new QGraphicsPixmapItem);

    hudBars.push_back(new QGraphicsPixmapItem);

    hudBars.push_back(new QGraphicsPixmapItem);

    scene = scene_;
    reset();

    int x = -190;
    int y = -140;
    for (auto i = hudBars.begin(); i != hudBars.end();++i){
        std::cout << "asd" << std::endl;

        (*i)->setPixmap(QPixmap("bar.png"));
        (*i)->setPos(x, y);
        x += 33;

        scene->addItem(*i);

    }
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
