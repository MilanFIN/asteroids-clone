#ifndef HUD_H
#define HUD_H

#include <QGraphicsPixmapItem>

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
};

#endif // HUD_H
