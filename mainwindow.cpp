#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1201, 871)),
    timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new QGraphicsPixmapItem(QPixmap(":/res/doodle.png"));
    scene->addItem(player);
    player->setPos(0, 0);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        player->setPos(player->x(), player->y() - 10);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        player->setPos(player->x(), player->y() + 10);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        player->setPos(player->x() - 10, player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        player->setPos(player->x() + 10, player->y());
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    bullet *b = new bullet;

    b->setPixmap(QPixmap(":/res/bullet.png").scaled(84, 178));
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}


































