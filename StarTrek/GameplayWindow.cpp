#include "GameplayWindow.h"

GameplayWindow::GameplayWindow(MainWindow* parent)
{
    // We need to give the parent focus
    parent_ = parent;
    parent_->setFocus();

    // Let's create the scene as well
    scene_ = new QGraphicsScene();
    setScene(scene_);
}

/************************
LEVEL 1
*************************/

LevelOne::LevelOne(MainWindow* parent) : GameplayWindow(parent)
{
    // Create the enterprise here
    player_ = new Enterprise(parent_->getEnterprise(),(parent_->getLevel1()->width()/2) - (parent_->getEnterprise()->width()/2),parent_->getLevel1()->height() - parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);

    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimer()));
    timer_->start();
}

void LevelOne::pause()
{
    timer_->stop();
}

void LevelOne::restart()
{
    timer_->start();
}

void LevelOne::drawBackground(QPainter *p, const QRectF &rect)
{
    QRectF newRect = rect;
    newRect = newRect;
    QPixmap* landscape_ = parent_->getLevel1();
    p->drawPixmap(QPoint(0,0),*landscape_);
    setSceneRect(0,0,landscape_->width(),landscape_->height());
    setFixedSize(landscape_->width()+10,landscape_->height()+10);
}

void LevelOne::handleTimer()
{
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
        things_[n]->move();
}

void LevelOne::leftArrow()
{
    player_->setVelocity(-10,0);
}

void LevelOne::rightArrow()
{
    player_->setVelocity(10,0);
}

void LevelOne::upArrow()
{
    // The player can't move up in this level
}
void LevelOne::downArrow()
{
    // The player can't move down in this level
}

void LevelOne::w()
{
    // TODO: Add phaser up code
}
void LevelOne::a()
{
    // The player can only shoot up in this level.
}
void LevelOne::d()
{
    // The player can only shot up in this level.
}
void LevelOne::x()
{
    // The player can only shoot up in this level.
}
