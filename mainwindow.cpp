#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QkeyEvent>
#include <QTimer>

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
    player->setPixmap(QPixmap("player.png"));
    player->setRotation(0);
    scene->addItem(player);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(20);


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
/*
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int angle = 0;
    if (event->key() == Qt::Key_Left){
        angle = -5;
    }
    else if (event->key() == Qt::Key_Right){
        angle = 5;
    }
    if (event->key() == Qt::Key_Up){
        player->accelerate();
    }

   player->setTransformOriginPoint(5,5);
   player->setRotation(player->rotation()+angle);

}
*/



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
}
