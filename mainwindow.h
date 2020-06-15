#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
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
    void gen_shield();
    void rm_bomb();

signals:
    void rm_bullet();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player, *fly, *bomb, *hole, *shield;
    QLabel *shield_icon;
    QTimer *timer;
    double v = 6.5, a = -0.05, score = 0, tmp_score = 0, lst_fly_gen = 0, lst_bomb_gen = 0, lst_hole_gen = 0, lst_shield_gen = -25000;
    bool paused = 0, overed = 0, protect = 0;
    std::multiset<platform_base*> plats;
    QPushButton *pause_button;
    void gen_plat(double, double);
    void roll(double);
    void over();
    bool colliding_with_fly();
    bool colliding_with_bomb();
    bool colliding_with_hole();
    bool colliding_with_shield();
};

#endif // MAINWINDOW_H














