


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "player.h"
#include "asteroid.h"
#include <vector>
#include "projectile.h"
#include "homing.h"
#include "mine.h"
#include "hud.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent( QKeyEvent* pEvent );
    void keyReleaseEvent( QKeyEvent* pEvent );

public slots:
    //called periodically to cause game object movement and check collisions
    void move();
    //called periodically to spawn asteroids or homing objects
    void asteroidSpawner();
    //-
    void allowFire();

private:
    //clears asteroids,mines,homings and projectiles from the scene and corresponding vectors
    void removeObjects();

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Player *player;
    Hud* hud;

    //variables to store keypress states, true if pressed
    bool left = false;
    bool right = false;
    bool up = false;
    bool space = false;
    bool control = false;
    bool spaceRead = false;


    std::vector<Asteroid*> asteroids;
    std::vector<Projectile*> projectiles;
    std::vector<Homing*> homings;
    std::vector<Mine*> mines;

};

#endif // MAINWINDOW_H
