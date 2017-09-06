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
    hudBars.at(0)->setVisible(true);
    hudBars.at(1)->setVisible(true);
    hudBars.at(2)->setVisible(true);
    hudBars.at(3)->setVisible(true);
    gameover = false;
    health = 4;
}

void Hud::hit()
{
    --health;
    if (health == 3){
        hudBars.at(3)->setVisible(false);
    }
    else if (health == 2){
        hudBars.at(2)->setVisible(false);
    }
    else if (health == 1){
        hudBars.at(1)->setVisible(false);
    }
    else if (health == 0){
        hudBars.at(0)->setVisible(false);
        gameover = true;
    }
}

bool Hud::gameOver()
{
    return gameover;
}
