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
        parent_->secondLevel();
        return;
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
        Asteroid* myAsteroid = new Asteroid(asteroids_[anotherDecision],parent_->getLevel1()->width(), aCounter+50, parent_->getLevel1()->width(), parent_->getLevel1()->height(),this);
        scene_->addItem(myAsteroid);
        things_.push_back(myAsteroid);
    }
    handleCollisions();
    aCounter = aCounter + 51;
}

void LevelOne::handleCollisions()
{
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++) {
        for (int i = 0; i < tSize; i++) {
            if (i == n)
                continue;
            if (things_[n]->collidesWithItem(things_[i]))
            {
                Phaser* pThing = dynamic_cast<Phaser*>(things_[n]);
                Enterprise* eThing = dynamic_cast<Enterprise*>(things_[n]);
                Asteroid* aThing = dynamic_cast<Asteroid*>(things_[n]);
                Phaser* pThing1 = dynamic_cast<Phaser*>(things_[i]);
                Enterprise* eThing1 = dynamic_cast<Enterprise*>(things_[i]);
                Asteroid* aThing1 = dynamic_cast<Asteroid*>(things_[i]);

                if (pThing && aThing1) {
                    // A phaser is hitting an asteroid
                    removeThings(pThing,aThing1);
                    tSize = things_.size();
                    parent_->changeScore(10);
                    return;
                }
                if (pThing1 && aThing) {
                    // A phaser is hitting an asteroid
                    removeThings(pThing1,aThing);
                    tSize = things_.size();
                    parent_->changeScore(10);
                    return;
                }
                if (aThing && eThing1) {
                    // The player has hit an asteroid
                    parent_->loseLife();
                    newLevel();
                    return;
                }
                if (aThing1 && eThing) {
                    // The player has hit an asteroid
                    parent_->loseLife();
                    newLevel();
                    return;
                }
            } // End if
        } // End of inner for loop
    } // End of main for loop
}

void LevelOne::newLevel()
{
    timer_->stop();
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        scene_->removeItem(*it);
    }
    things_.clear();

    // Create the enterprise here
    player_ = new Enterprise(parent_->getEnterprise(),(parent_->getLevel1()->width()/2) - (parent_->getEnterprise()->width()/2),parent_->getLevel1()->height() - parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);

    aCounter = 0;
    timer_->start();
}

void LevelOne::asteroidCleared()
{
    parent_->changeScore(5);
}

void LevelOne::removeThings(Thing* item1, Thing* item2)
{
    bool removed1 = false;
    bool removed2 = false;
    scene_->removeItem(item1);
    scene_->removeItem(item2);
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        if (*it == NULL) {
            break;
        }
        if (*it == item1) {
            if (removed1)
                continue;
            things_.erase(it);
            removed1 = true;
            continue;
        }
        if (*it == item2) {
            if (removed2)
                continue;
            things_.erase(it);
            removed2 = true;
            continue;
        }
    }
}

void LevelOne::removeThing(Thing* item)
{
    //Remove the thing from the vector
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        if (*it == NULL)
            break;
        if (*it == item) {
            things_.erase(it);
            scene_->removeItem(item);
        }
    }
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
    Phaser* myPhaser = new Phaser(parent_->getRedPhaser(),player_->pos().x() + (parent_->getEnterprise()->width()/2),player_->pos().y() - parent_->getEnterprise()->height() -1,0,-20,parent_->getLevel1()->width(),parent_->getLevel1()->height(),this);
    scene_->addItem(myPhaser);
    things_.push_back(myPhaser);
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



/***********************************
LEVEL TWO
************************************/
LevelTwo::LevelTwo(MainWindow* parent) : GameplayWindow(parent)
{
    // Create the romulan

}

void LevelTwo::newLevel()
{

}

void LevelTwo::handleTimer()
{

}

void LevelTwo::handleCollisions()
{

}

void LevelTwo::pause()
{
    timer_->stop();
}

void LevelTwo::restart()
{
    timer_->start();
}

void LevelTwo::removeThing(Thing* item)
{

}

void LevelTwo::leftArrow()
{

}

void LevelTwo::rightArrow()
{

}

void LevelTwo::upArrow()
{

}

void LevelTwo::downArrow()
{

}

void LevelTwo::w()
{

}

void LevelTwo::a()
{

}

void LevelTwo::d()
{

}

void LevelTwo::x()
{

}

void LevelTwo::drawBackground(QPainter* p, const QRectF &rect)
{
    QRectF newRect = rect;
    newRect = newRect;
    QPixmap* landscape_ = parent_->getLevel2();
    p->drawPixmap(QPoint(0,0),*landscape_);
    setSceneRect(0,0,landscape_->width(),landscape_->height());
    setFixedSize(landscape_->width()+10,landscape_->height()+10);
}



