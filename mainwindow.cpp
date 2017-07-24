#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QkeyEvent>
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
    asteroidSpawnTimer->start(100);

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
}



void MainWindow::move()
{

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
    player->move();


    for(std::vector<Asteroid*>::iterator i = asteroids.begin(); i != asteroids.end();/* ++i*/) {
        (*i)->move();
        if ((*i)->getx() > 1000 || (*i)->getx() < -1000 || (*i)->gety() > 1000 || (*i)->gety() < -1000){
            scene->removeItem(*i);
            i = asteroids.erase(i);
            //std::cout << "removed" << std::endl;
        } else {
            ++i;
        }
    }
}

void MainWindow::asteroidSpawner()
{
    Asteroid* newAsteroid = new Asteroid(0);
    asteroids.push_back(newAsteroid);
    scene->addItem(newAsteroid);
    //std::cout << "spawned" << std::endl;

}
