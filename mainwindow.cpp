#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
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
    scene->setSceneRect(-200, -150, 398, 298);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));

    player = new Player;
    player->setRotation(0);
    scene->addItem(player);


    hud = new Hud(scene);



    //init srand to later create asteroids at random locations
    srand((unsigned)std::time(0));



    //init timer that causes a signal to apply player movement
    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(20);

    QTimer *asteroidSpawnTimer = new QTimer(this);
    connect(asteroidSpawnTimer, SIGNAL(timeout()), this, SLOT(asteroidSpawner()));
    asteroidSpawnTimer->start(1000);

    QTimer *firingTimer = new QTimer(this);
    connect(firingTimer, SIGNAL(timeout()), this, SLOT(allowFire()));
    firingTimer->start(100);

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
    if (event->key() == Qt::Key_Control){
        control = true;
    }
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        //reset gamestate to start
        hud->reset();
        player->resetPos();
        removeObjects();
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
    if (event->key() == Qt::Key_Control){
        control = false;
    }
}



void MainWindow::move()
{
    setFocus(); //in case of clicking something on the background


    if (!hud->gameOver()){
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

        if (space && !spaceRead){
            Projectile* newProjectile = new Projectile(player->x(), player->y(), player->rotation());
            projectiles.push_back(newProjectile);
            scene->addItem(newProjectile);
            space = false;
            spaceRead = true;
        }
        if (control){

            Mine* newMine = new Mine(player);
            mines.push_back(newMine);
            scene->addItem(newMine);
            control = false;
        }

    }


    player->move();


    //move asteroids
    for(std::vector<Asteroid*>::iterator i = asteroids.begin(); i != asteroids.end();) {
        (*i)->move();
        bool removeAsteroid = false;
        for (std::vector<Mine*>::iterator j = mines.begin(); j != mines.end();){
            if ((*i)->collidesWithItem((*j))){ //should no longer cause problems
                scene->removeItem(*j);
                delete *j;
                j = mines.erase(j);
                removeAsteroid = true;
                break;
            } else {
                ++j;
            }
        }

        if (removeAsteroid){
            float tempAngle = (*i)->getAngle();
            int tempX = (*i)->getx();
            int tempY = (*i)->gety();
            int tempSize = (*i)->size();
            scene->removeItem(*i);
            delete *i;
            i = asteroids.erase(i);
            if (tempSize > 0){
                //add new asteroids to the location of the removed one, directions +-10 degrees
                //and location is the same
                Asteroid* newAsteroid0 = new Asteroid(tempSize -1, tempX, tempY, tempAngle-10);
                asteroids.push_back(newAsteroid0);
                scene->addItem(newAsteroid0);
                Asteroid* newAsteroid1 = new Asteroid(tempSize -1, tempX, tempY, tempAngle+10);
                asteroids.push_back(newAsteroid1);
                scene->addItem(newAsteroid1);
            }
        }
        else if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000){
            scene->removeItem(*i);
            delete *i;
            i = asteroids.erase(i);
        }
        else if (player->collidesWithItem((*i))){
            scene->removeItem(*i);
            delete *i;

            i = asteroids.erase(i);
            //player damage trigger goes here.
            hud->hit();


        } else {
            ++i;
        }

    }


    //move projectiles
    for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end();){
        (*i)->move();
        bool remove = false;


        //check for asteroid collisions with projectile
        for (std::vector<Asteroid*>::iterator j = asteroids.begin(); j != asteroids.end();){
            if ((*i)->collidesWithItem((*j))){
                float tempAngle = (*j)->getAngle();
                int tempX = (*j)->getx();
                int tempY = (*j)->gety();
                int tempSize = (*j)->size();

                scene->removeItem((*j));
                delete *j;
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

        //projectile collisions with missiles
        for (std::vector<Homing*>::iterator j = homings.begin(); j != homings.end();){
            if ((*i)->collidesWithItem((*j))){
                scene->removeItem((*j));
                delete *j;
                j = homings.erase(j);
                remove = true;
            }
            else {
                ++j;
            }

        }

        if (remove){
            scene->removeItem(*i);
            delete *i;
            i = projectiles.erase(i);
        }
        else if ((*i)->getx() > 210 || (*i)->getx() < -210 || (*i)->gety() > 160 || (*i)->gety() < -160){
            scene->removeItem(*i);
            delete *i;
            i = projectiles.erase(i);
        } else{
            ++i;

        }
    }




    //move homingmissiles
    for(std::vector<Homing*>::iterator i = homings.begin(); i != homings.end();) {
        (*i)->move(player);
        //check if the missile collides with any mines
        bool removeHoming = false;
        for (std::vector<Mine*>::iterator j = mines.begin(); j != mines.end();){
            if ((*i)->collidesWithItem((*j))){
                scene->removeItem(*j);
                delete *j;
                j = mines.erase(j);
                removeHoming = true;
                break;
            } else {
                ++j;
            }
        }

        if (removeHoming){
            scene->removeItem(*i);
            delete *i;
            i = homings.erase(i);
        }
        else if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000){
            scene->removeItem(*i);
            delete *i;
            i = homings.erase(i);
        }
        else if (player->collidesWithItem((*i))){
            scene->removeItem(*i);
            delete *i;
            i = homings.erase(i);
            //player damage trigger goes here.
            hud->hit();

        } else {
            ++i;
        }

    }

    //move mines
    for(std::vector<Mine*>::iterator i = mines.begin(); i != mines.end();){
        (*i)->move();
        if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000 || (*i)->getAge() > 8){
            scene->removeItem(*i);
            delete *i;
            i = mines.erase(i);

        } else {
            ++i;
        }

    }



}

void MainWindow::asteroidSpawner()
{

    int size = (rand()%3);
    if (size < 2){
        Asteroid* newAsteroid = new Asteroid(size);
        asteroids.push_back(newAsteroid);
        scene->addItem(newAsteroid);
    }
    else {
        Homing* newHoming = new Homing(player);
        homings.push_back(newHoming);
        scene->addItem(newHoming);
    }



}

void MainWindow::allowFire()
{
    spaceRead = false;
}

void MainWindow::removeObjects()
{
    for (auto i = projectiles.begin(); i != projectiles.end();++i){
        scene->removeItem(*i);
        delete *i;
    }
    projectiles.clear();

    for (auto i = mines.begin(); i != mines.end();++i){
        scene->removeItem(*i);
        delete *i;
    }
    mines.clear();

    for (auto i = asteroids.begin(); i != asteroids.end();++i){
        scene->removeItem(*i);
        delete *i;
    }
    asteroids.clear();

    for (auto i = homings.begin(); i != homings.end();++i){
        scene->removeItem(*i);
        delete *i;
    }
    homings.clear();
}
