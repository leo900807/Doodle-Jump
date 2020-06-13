#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1000, 830)),
    timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/res/doodle.png"));
    scene->addItem(player);
    player->setPos(500 - player->pixmap().width() / 2, 830 - player->pixmap().height());
    timer->start(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gen_fly()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gen_bomb()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gen_hole()));
    srand(time(NULL));
    for(int i = 0; i < 4; i++)
    {
        gen_plat(rand() % (1000 - 100), rand() % (830 / 5) + (830 / 5) * i);
        if(rand() % 20 < 3)
            gen_plat(rand() % (1000 - 100), rand() % (830 / 5) + (830 / 5) * i);
    }
    for(int i = 0; i < 10; i++)
    {
        gen_plat(rand() % (1000 - 100), -(rand() % (1660 / 10) + (1660 / 10) * i));
        if(rand() % 20 < 3)
            gen_plat(rand() % (1000 - 100), -(rand() % (1660 / 10) + (1660 / 10) * i));
    }
    normal_platform *plat = new normal_platform(0, 830);
    plat->setPixmap(QPixmap(":/res/normal_platform.png").scaled(1000, 100));
    plats.insert(plat);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(plat));
    pause_button = new QPushButton(this);
    pause_button->setIcon(QPixmap(":/res/pause_icon.png").scaled(45, 45));
    pause_button->setGeometry(970, 20, 45, 45);
    pause_button->setIconSize(QPixmap(":/res/pause_icon.png").rect().size());
    connect(pause_button, SIGNAL(clicked()), this, SLOT(pause()));
    fly = new QGraphicsPixmapItem(QPixmap(":/res/fly.jpg").scaled(50, 50));
    fly->setPos(-1000, 1300);
    scene->addItem(fly);
    bomb = new QGraphicsPixmapItem(QPixmap(":/res/bomb.png").scaled(100, 100));
    bomb->setPos(-1000, 1300);
    scene->addItem(bomb);
    hole = new QGraphicsPixmapItem(QPixmap(":/res/hole.png").scaled(200, 200));
    hole->setPos(-1000, 1300);
    scene->addItem(hole);
    ui->lose_label->hide();
    ui->score_name->hide();
    ui->score_label->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::jump()
{
    if(v <= -12)
        over();
    if(player->y() <= 400)
        roll(v);
    else
        player->setPos(player->x(), player->y() - v);
    v += a;
    if(colliding_with_bomb() || colliding_with_hole())
        return over(), void();
    if(colliding_with_fly())
        v = 15;
    else
        for(auto plat : plats)
            if(player->x() + player->pixmap().width() > plat->x() && player->x() < plat->x() + plat->pixmap().width() && abs(plat->y() - player->y() - player->pixmap().height()) <= 5 && v < 0)
            {
                v = 6.5;
                if(plat->be_jumped())
                    plats.erase(plat);
                break;
            }
    tmp_score += v;
    score = std::max(tmp_score, score);
    ui->score_bar->display(QString::number(int(score / 10)));
}

void MainWindow::pause()
{
    if(overed)
        return;
    paused ^= 1;
    if(paused)
    {
        pause_button->setIcon(QPixmap(":/res/start_icon.png").scaled(50, 50));
        timer->stop();
    }
    else
    {
        pause_button->setIcon(QPixmap(":/res/pause_icon.png").scaled(50, 50));
        timer->start(5);
    }
}

void MainWindow::gen_fly()
{
    if(score - lst_fly_gen >= 10000 && rand() % 200 < 2)
    {
        fly->setPos(rand() % (1000 - fly->pixmap().width()), -rand() % 500);
        lst_fly_gen = score;
    }
}

void MainWindow::gen_bomb()
{
    if(score - lst_bomb_gen >= 15000 && rand() % 200 < 2)
    {
        bomb->setPos(rand() % (1000 - bomb->pixmap().width()), -rand() % 500);
        lst_bomb_gen = score;
    }
}

void MainWindow::gen_hole()
{
    if(score - lst_hole_gen >= 20000 && rand() % 200 < 2)
    {
        hole->setPos(rand() % (1000 - hole->pixmap().width()), -rand() % 500);
        lst_hole_gen = score;
    }
}

void MainWindow::gen_plat(double x = -1100, double y = -1100)
{
    if(plats.size() > 40)
        return;
    platform_base *plat;
    if(x <= -1000 && y <= -1000)
        if(rand() % 20 < 1)
            plat = new fragile_platform(rand() % (1000 - 100), -(rand() % 100 + 100));
        else
            plat = new normal_platform(rand() % (1000 - 100), -(rand() % 100 + 100));
    else
    {
        if(rand() % 20 < 1)
            plat = new fragile_platform(x, y);
        else
            plat = new normal_platform(x, y);
        if(rand() % 30 < 1)
            if(rand() % 20 < 1)
                plat = new fragile_platform(x, y);
            else
                plat = new normal_platform(x, y);
    }
    plats.insert(plat);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(plat));
}

void MainWindow::roll(double v)
{
    for(auto plat : plats)
    {
        plat->setPos(plat->x(), plat->y() + v);
        if(plat->y() >= 1300)
        {
            gen_plat();
            delete plat;
            plats.erase(plat);
        }
    }
    fly->setPos(fly->x(), fly->y() + v);
    bomb->setPos(bomb->x(), bomb->y() + v);
    hole->setPos(hole->x(), hole->y() + v);
}

void MainWindow::over()
{
    overed = 1;
    timer->stop();
    for(auto plat : plats)
        plat->hide();
    player->hide();
    fly->hide();
    bomb->hide();
    hole->hide();
    ui->lose_label->show();
    ui->score_name->show();
    ui->score_label->show();
    ui->score_label->setNum(int(score / 10));
}

bool MainWindow::colliding_with_fly()
{
    return player->x() + player->pixmap().width() >= fly->x() && player->x() <= fly->x() + fly->pixmap().width() && player->y() + player->pixmap().height() >= fly->y() && player->y() <= fly->y() + fly->pixmap().height();
}

bool MainWindow::colliding_with_bomb()
{
    return player->x() + player->pixmap().width() >= bomb->x() && player->x() <= bomb->x() + bomb->pixmap().width() && player->y() + player->pixmap().height() >= bomb->y() && player->y() <= bomb->y() + bomb->pixmap().height();
}

bool MainWindow::colliding_with_hole()
{
    return player->x() + player->pixmap().width() >= hole->x() && player->x() <= hole->x() + hole->pixmap().width() && player->y() + player->pixmap().height() >= hole->y() && player->y() <= hole->y() + hole->pixmap().height();
}

void MainWindow::rm_bomb()
{
    bomb->setPos(-1000, -1300);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(overed)
        return;
    if(e->key() == Qt::Key_P)
        pause();
    if(paused)
        return;
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        player->setPos(player->x() - 20, player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        player->setPos(player->x() + 20, player->y());
        break;
    case Qt::Key_Space:
        bullet *b = new bullet(bomb->x(), bomb->y(), bomb->pixmap().width(), bomb->pixmap().height());

        b->setPixmap(QPixmap(":/res/bullet.png").scaled(84, 178));
        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        b->connect(b, SIGNAL(explode()), this, SLOT(rm_bomb()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        break;
    }
    if(player->x() + player->pixmap().width() / 2 > 1000)
        player->setPos(-player->pixmap().width() / 2, player->y());
    else if(player->x() + player->pixmap().width() / 2 < 0)
        player->setPos(1000 - player->pixmap().width() / 2, player->y());
}


































