#include "GameplayWindow.h"
#include <iostream>

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

    aCounter = 0;
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
    if (aCounter > 20000) {
        // Insert code to move to level 2
    }
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
        things_[n]->move();

    // Decide whether to create an asteroid
    int a = 50-(aCounter/200);
    if (a < 10)
        a = 10;
    int randSeed = 200 + aCounter;
    srand(randSeed);
    int decide = rand() % a + 1;
    if (decide == 1) {
        // Decide on a picture
        int aSize;
        QPixmap** asteroids_ = parent_->getAsteroids(aSize);
        int anotherDecision = rand() % aSize;
        Asteroid* myAsteroid = new Asteroid(asteroids_[anotherDecision],parent_->getLevel1()->width(), aCounter+50);
        scene_->addItem(myAsteroid);
        things_.push_back(myAsteroid);
    }
    aCounter = aCounter + 51;
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
