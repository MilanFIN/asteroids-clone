#ifndef HUD_H
#define HUD_H

#include <QGraphicsPixmapItem>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsItem>


class Hud
{
public:
    Hud();
    Hud(QGraphicsScene* scene_);
    void reset();
    void hit();
    bool gameOver();
private:
    QGraphicsScene* scene;
    bool gameover;
    int health;
    std::vector<QGraphicsPixmapItem*> hudBars;
};

#endif // HUD_H
