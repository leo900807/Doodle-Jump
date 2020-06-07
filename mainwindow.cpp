#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 600, 830)),
    timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/res/doodle.png"));
    scene->addItem(player);
    player->setPos(300 - player->pixmap().width() / 2, 830 - player->pixmap().height());
    timer->start(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
    srand(time(NULL));
    for(int i = 0; i < 5; i++)
    {
        QGraphicsPixmapItem *plat = new QGraphicsPixmapItem(QPixmap(":/res/normal_platform.png").scaled(100, 50));
        plat->setPos(rand() % (600 - plat->pixmap().width()), rand() % (830 / 5) + (830 / 5) * i);
        plats.insert(plat);
        scene->addItem(plat);
        if(rand() % 20 < 3)
        {
            plat = new QGraphicsPixmapItem(QPixmap(":/res/normal_platform.png").scaled(100, 50));
            plat->setPos(rand() % (600 - plat->pixmap().width()), rand() % (830 / 5) + (830 / 5) * i);
            plats.insert(plat);
            scene->addItem(plat);
        }
    }
    for(int i = 0; i < 10; i++)
    {
        QGraphicsPixmapItem *plat = new QGraphicsPixmapItem(QPixmap(":/res/normal_platform.png").scaled(100, 50));
        plat->setPos(rand() % (600 - plat->pixmap().width()), -(rand() % (1660 / 10) + (1660 / 10) * i));
        plats.insert(plat);
        scene->addItem(plat);
        if(rand() % 20 < 3)
        {
            plat = new QGraphicsPixmapItem(QPixmap(":/res/normal_platform.png").scaled(100, 50));
            plat->setPos(rand() % (600 - plat->pixmap().width()), -(rand() % (1660 / 10) + (1660 / 10) * i));
            plats.insert(plat);
            scene->addItem(plat);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::jump()
{
    QList<QGraphicsItem*> colli = player->collidingItems();
    if(v <= -12)
        over();
    if(player->y() <= 430)
        roll(v);
    else
        player->setPos(player->x(), player->y() - v);
    v += a;
    for(auto plat : plats)
        if(player->x() + player->pixmap().width() > plat->x() && player->x() < plat->x() + plat->pixmap().width() && abs(plat->y() - player->y() - player->pixmap().height()) <= 3.5 && v < 0)
        {
            v = 6.5;
            break;
        }
    if(player->y() + player->pixmap().height() >= 830)
        v = 6.5;
}

void MainWindow::gen_plat()
{
    if(plats.size() > 20)
        return;
    QGraphicsPixmapItem *plat = new QGraphicsPixmapItem(QPixmap(":/res/normal_platform.png").scaled(100, 50));
    plat->setPos(rand() % (600 - plat->pixmap().width()), -(rand() % 200 + 200));
    plats.insert(plat);
    scene->addItem(plat);
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
}

void MainWindow::over()
{
    timer->stop();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        player->setPos(player->x(), player->y() - 20);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        player->setPos(player->x(), player->y() + 20);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        player->setPos(player->x() - 20, player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        player->setPos(player->x() + 20, player->y());
        break;
    case Qt::Key_Space:
        bullet *b = new bullet;

        b->setPixmap(QPixmap(":/res/bullet.png").scaled(84, 178));
        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        break;
    }
    if(player->x() + player->pixmap().width() / 2 > 600)
        player->setPos(-player->pixmap().width() / 2, player->y());
    else if(player->x() + player->pixmap().width() / 2 < 0)
        player->setPos(600 - player->pixmap().width() / 2, player->y());
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    bullet *b = new bullet;

    b->setPixmap(QPixmap(":/res/bullet.png").scaled(84, 178));
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}


































