#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPushButton>
#include <set>

#include "bullet.h"
#include "platform.h"

#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    void jump();
    void pause();
    void gen_fly();
    void gen_bomb();
    void gen_hole();
    void rm_bomb();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player, *fly, *bomb, *hole;
    QTimer *timer;
    double v = 6.5, a = -0.05, score = 0, tmp_score = 0, lst_fly_gen = 0, lst_bomb_gen = 0, lst_hole_gen = 0;
    bool paused = 0, overed = 0;
    std::multiset<platform_base*> plats;
    QPushButton *pause_button;
    void gen_plat(double, double);
    void roll(double);
    void over();
    bool colliding_with_fly();
    bool colliding_with_bomb();
    bool colliding_with_hole();
};

#endif // MAINWINDOW_H














