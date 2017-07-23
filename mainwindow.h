#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QgraphicsItem>
#include "player.h"
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
    void move();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Player *player;

    bool left = false;
    bool right = false;
    bool up = false;
};

#endif // MAINWINDOW_H
