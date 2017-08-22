#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
#include "asteroid.h"

#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene = new QGraphicsScene(this);


    ui->graphicsView->setScene(scene);

    // anti-aliasing
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // The bounding rectangle of the scene
    // The scene rectangle defines the extent of the scene.
    // It is primarily used by QGraphicsView
    // to determine the view's default scrollable area,
    // and by QGraphicsScene to manage item indexing.

    scene->setSceneRect(-200, -150, 398, 298);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));

    player = new Player;
    player->setRotation(0);
    scene->addItem(player);


    //init srand to later create asteroids at random locations
    srand((unsigned)std::time(0));



    //init timer that causes a signal to apply player movement
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(20);

    QTimer *asteroidSpawnTimer = new QTimer(this);
    connect(asteroidSpawnTimer, SIGNAL(timeout()), this, SLOT(asteroidSpawner()));
    asteroidSpawnTimer->start(1000);

    //setFocusPolicy(QMainWindow::);
    setFocus();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        left = true;
    }
    else if (event->key() == Qt::Key_Right){
        right = true;
    }
    if (event->key() == Qt::Key_Up){
        up = true;
    }
    if (event->key() == Qt::Key_Space){
        space = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        left = false;
    }
    else if (event->key() == Qt::Key_Right){
        right = false;
    }
    if (event->key() == Qt::Key_Up){
        up = false;
    }
    if (event->key() == Qt::Key_Space){
        space = false;
    }
}



void MainWindow::move()
{
    setFocus(); //in case of clicking something on the background

    if (left){
        player->setTransformOriginPoint(5,5);
        player->setRotation(player->rotation()-5);
    }
    if (right){
        player->setTransformOriginPoint(5,5);
        player->setRotation(player->rotation()+5);
    }
    if (up){
        player->accelerate();
    }


    if (space){
        Projectile* newProjectile = new Projectile(player->x(), player->y(), player->rotation());
        projectiles.push_back(newProjectile);
        scene->addItem(newProjectile);
        space = false;
    }


    player->move();



    for(std::vector<Asteroid*>::iterator i = asteroids.begin(); i != asteroids.end();) {
        (*i)->move();
        if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000){
            scene->removeItem(*i);
            i = asteroids.erase(i);

        }
        else if (player->collidesWithItem((*i))){
            scene->removeItem(*i);
            i = asteroids.erase(i);

            //player damage trigger goes here.


        } else {
            ++i;
        }

    }


    for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end();){
        (*i)->move();
        bool remove = false;
        for (std::vector<Asteroid*>::iterator j = asteroids.begin(); j != asteroids.end();){

            if ((*i)->collidesWithItem((*j))){
                float tempAngle = (*j)->getAngle();
                int tempX = (*j)->getx();
                int tempY = (*j)->gety();
                int tempSize = (*j)->size();

                scene->removeItem((*j));
                j = asteroids.erase(j);
                remove = true;
                if (tempSize == 0){

                    break;
                }
                if (tempSize > 0){
                    //add new asteroids to the location of the removed one, directions +-10 degrees
                    //and location is the same
                    Asteroid* newAsteroid0 = new Asteroid(tempSize -1, tempX, tempY, tempAngle-10);
                    asteroids.push_back(newAsteroid0);
                    scene->addItem(newAsteroid0);
                    Asteroid* newAsteroid1 = new Asteroid(tempSize -1, tempX, tempY, tempAngle+10);
                    asteroids.push_back(newAsteroid1);
                    scene->addItem(newAsteroid1);


                    break;
                }
            }
            else {
                ++j;
            }

        }
        if (remove){
            scene->removeItem(*i);
            i = projectiles.erase(i);
        }
        else if ((*i)->getx() > 210 || (*i)->getx() < -210 || (*i)->gety() > 160 || (*i)->gety() < -160){
            scene->removeItem(*i);
            i = projectiles.erase(i);
        } else{
            ++i;

        }
    }



    for(std::vector<Homing*>::iterator i = homings.begin(); i != homings.end();) {
        (*i)->move(player);
        if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000){
            scene->removeItem(*i);
            i = homings.erase(i);

        }
        else if (player->collidesWithItem((*i))){
            scene->removeItem(*i);
            i = homings.erase(i);

            //player damage trigger goes here.


        } else {
            ++i;
        }

    }




}

void MainWindow::asteroidSpawner()
{

    int size = (rand()%2);

    Asteroid* newAsteroid = new Asteroid(size);
    asteroids.push_back(newAsteroid);
    scene->addItem(newAsteroid);

    Homing* newHoming = new Homing(player);
    homings.push_back(newHoming);
    scene->addItem(newHoming);


}
