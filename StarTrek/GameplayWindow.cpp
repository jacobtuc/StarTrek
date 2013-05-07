#include "GameplayWindow.h"
#include <math.h>
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
            break;
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
    playerHealth = 100;
    warbirdHealth = 100;

    // Create the enterprise
    player_ = new Enterprise(parent_->getEnterprise(),0,parent_->getLevel2()->height()-parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);

    // Create the warbird
    warbird_ = new Warbird(parent_->getRomulan(),0,0,parent_->getLevel2()->width(),parent_->getLevel2()->height());
    warbird_->rotate(180);
    warbird_->setPos(parent_->getLevel2()->width() - parent_->getRomulan()->width(),0);
    scene_->addItem(warbird_);
    things_.push_back(warbird_);

    // Create and start the timer
    counter_ = 0;
    phaserCount = 60;
    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_,SIGNAL(timeout()),this,SLOT(handleTimer()));
    timer_->start();
}

void LevelTwo::newLevel()
{
    timer_->stop();
    counter_ = 0;
    phaserCount = 60;
    playerHealth = 100;
    warbirdHealth = 100;

    // Delete stuff
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
        scene_->removeItem(things_[n]);
    things_.clear();

    // Create the enterprise
    player_ = new Enterprise(parent_->getEnterprise(),0,parent_->getLevel2()->height()-parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);

    // Create the warbird
    warbird_ = new Warbird(parent_->getRomulan(),0,0,parent_->getLevel2()->width(),parent_->getLevel2()->height());
    warbird_->rotate(180);
    warbird_->setPos(parent_->getLevel2()->width() - parent_->getRomulan()->width(),0);
    scene_->addItem(warbird_);
    things_.push_back(warbird_);

    timer_->start();
}

void LevelTwo::handleTimer()
{
    if (counter_ == phaserCount) {
        // Create the romulan phaser
        int pVX,pVY,xd,yd,x0,y0;
        if (player_->pos().x() < warbird_->pos().x())
        {
            // The player is to the left of the warbird
            if (player_->pos().y() < warbird_->pos().y())
            {
                // The player is to the left and above the warbird
                x0 = warbird_->pos().x()-parent_->getRomulan()->width()-1-parent_->getGreenPhaser()->width();
                y0 = warbird_->pos().y() - parent_->getRomulan()->height() - 1-parent_->getGreenPhaser()->height();
            } else {
                // The player is to the left and below the warbird
                x0 = warbird_->pos().x()-parent_->getRomulan()->width()-1-parent_->getGreenPhaser()->width();
                y0 = warbird_->pos().y() +1;

            }
        } else {
            // The player is to the right of the warbird
            if (player_->pos().y() < warbird_->pos().y()) {
                // The player is to the right and above the warbird
                x0 = warbird_->pos().x()+1;
                y0 = warbird_->pos().y()-parent_->getRomulan()->height()-1-parent_->getGreenPhaser()->height();
            } else {
                // THe player is to the right and below the warbird
                x0 = warbird_->pos().x()+1;
                y0 = warbird_->pos().y()+1;
            }
        }

        // We want the total velocity to be 15, so we have to calculate based on the velocity constraint
        xd = player_->pos().x()+(parent_->getEnterprise()->width()/2);
        yd = player_->pos().y()+(parent_->getEnterprise()->height()/2);
        int numerator = ((xd-x0)*(xd-x0)) + ((yd - y0)*(yd-y0));
        int t = static_cast<int>(sqrt(numerator/225));
        if (t != 0) {
            pVX = (xd-x0)/t;
            pVY = (yd-y0)/t;
            Phaser* aPhaser = new Phaser(parent_->getGreenPhaser(),x0,y0,pVX,pVY,parent_->getLevel2()->width(),parent_->getLevel2()->height(),this);
            scene_->addItem(aPhaser);
            things_.push_back(aPhaser);
        }
        // Reset phaser count for next time
        phaserCount = counter_ + 60;

    } // End phaser creation

    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
    {
        things_[n]->move();
    }

    handleCollisions();

    counter_++;
}

void LevelTwo::handleCollisions()
{
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
    {
        for (int i = 0; i < tSize; i++)
        {
            if (i == n)
                continue;
            if (things_[n]->collidesWithItem(things_[i]))
            {
                Phaser* pThing = dynamic_cast<Phaser*>(things_[n]);
                Enterprise* eThing = dynamic_cast<Enterprise*>(things_[n]);
                Warbird* wThing = dynamic_cast<Warbird*>(things_[n]);
                Phaser* pThing1 = dynamic_cast<Phaser*>(things_[i]);
                Enterprise* eThing1 = dynamic_cast<Enterprise*>(things_[i]);
                Warbird* wThing1 = dynamic_cast<Warbird*>(things_[i]);

                if (pThing && eThing1)
                {
                    // A phaser has hit the enterprise
                    removeThing(pThing);
                    decreaseEnterpriseHealth();
                    return;
                }
                if (eThing && pThing1)
                {
                    //A phaser has hit the enterprise
                    removeThing(pThing1);
                    decreaseEnterpriseHealth();
                    return;
                }
                if (pThing && wThing1)
                {
                    //A phaser has hit the warbird
                    removeThing(pThing);
                    decreaseWarbirdHealth();
                    return;
                }
                if (wThing && pThing1)
                {
                    //A phaser has hit the warbird
                    removeThing(pThing1);
                    decreaseWarbirdHealth();
                    return;
                }
                if (wThing && eThing1)
                {
                    //The enterprise has hit the warbird
                    parent_->loseLife();
                    newLevel();
                    return;
                }
                if (eThing && wThing1)
                {
                    //The enterprise has hit the warbird
                    parent_->loseLife();
                    newLevel();
                    return;
                }
            }

        }// End inner for loop
    }//End main for loop
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
    //Remove the thing from the vector
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        if (*it == NULL)
            break;
        if (*it == item) {
            things_.erase(it);
            scene_->removeItem(item);
            break;
        }
    }
}

void LevelTwo::leftArrow()
{
    player_->setVelocityX(-10);
}

void LevelTwo::rightArrow()
{
    player_->setVelocityX(10);
}

void LevelTwo::upArrow()
{
    player_->setVelocityY(-10);
}

void LevelTwo::downArrow()
{
    player_->setVelocityY(10);
}

void LevelTwo::w()
{
    // Create a new phaser above the neterprise and moving forward
    int x0,y0,mx,my;
    x0 = player_->pos().x() + (parent_->getEnterprise()->width()/2);
    y0 = player_->pos().y() - parent_->getRedPhaser()->height()-1;
    mx = parent_->getLevel2()->width();
    my = parent_->getLevel2()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,0,-15,mx,my,this);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelTwo::a()
{
    // Create a new phaser to the left of the enterprise and moving to the left.
    int x0,y0,mx,my;
    x0 = player_->pos().x() - parent_->getRedPhaser()->height()-1;
    y0 = player_->pos().y() + (parent_->getEnterprise()->height()/2);
    mx = parent_->getLevel2()->width();
    my = parent_->getLevel2()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,-15,0,mx,my,this);
    aPhaser->rotate(-90);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelTwo::d()
{
    int x0,y0,mx,my;
    x0 = player_->pos().x() + parent_->getEnterprise()->width() + parent_->getRedPhaser()->height()+1;
    y0 = player_->pos().y() + (parent_->getEnterprise()->height()/2);
    mx = parent_->getLevel2()->width();
    my = parent_->getLevel2()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,15,0,mx,my,this);
    aPhaser->rotate(90);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelTwo::x()
{
    int x0,y0,mx,my;
    x0 = player_->pos().x() + (parent_->getEnterprise()->width()/2);
    y0 = player_->pos().y() + parent_->getEnterprise()->height()+1;
    mx = parent_->getLevel2()->width();
    my = parent_->getLevel2()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,0,15,mx,my,this);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
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

void LevelTwo::decreaseWarbirdHealth()
{
    warbirdHealth = warbirdHealth - 20;

    if (warbirdHealth <= 0) {
        parent_->thirdLevel();
    }
}

void LevelTwo::decreaseEnterpriseHealth()
{
    playerHealth = playerHealth - 20;

    if (playerHealth <= 0)
        newLevel();
}



/****************************
LEVEL 3
*****************************/
LevelThree::LevelThree(MainWindow* parent) : GameplayWindow(parent)
{
    // Create the enterprise
    player_ = new Enterprise(parent_->getEnterprise(),0,parent_->getLevel3()->height() - parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);

    // Create the borg
    int xb0 = (parent_->getLevel3()->width()/2) - (parent_->getBorg()->width()/2);
    int yb0 = (parent_->getLevel3()->height()/2) - (parent_->getBorg()->height()/2);
    int mx = parent_->getLevel3()->width();
    int my = parent_->getLevel3()->height();
    Borg* theBorg = new Borg(parent_->getBorg(),xb0,yb0,mx,my);
    scene_->addItem(theBorg);
    things_.push_back(theBorg);

    // Create the first three ships of the fleet

    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_,SIGNAL(timeout()),this,SLOT(handleTimer()));
    timer_->start();
}

void LevelThree::removeThing(Thing* item)
{
    //Remove the thing from the vector
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        if (*it == NULL)
            break;
        if (*it == item) {
            things_.erase(it);
            scene_->removeItem(item);
            break;
        }
    }
}

void LevelThree::drawBackground(QPainter* p, const QRectF& rect)
{
    QRectF newRect = rect;
    newRect = newRect;
    QPixmap* landscape_ = parent_->getLevel3();
    p->drawPixmap(QPoint(0,0),*landscape_);
    setSceneRect(0,0,landscape_->width(),landscape_->height());
    setFixedSize(landscape_->width()+10,landscape_->height()+10);
}

void LevelThree::handleTimer()
{
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
        things_[n]->move();
}

void LevelThree::pause()
{
    timer_->stop();
}

void LevelThree::restart()
{
    timer_->start();
}

void LevelThree::leftArrow()
{
    player_->setVelocityX(-10);
}

void LevelThree::rightArrow()
{
    player_->setVelocityX(10);
}

void LevelThree::downArrow()
{
    player_->setVelocityY(10);
}

void LevelThree::upArrow()
{
    player_->setVelocityY(-10);
}

void LevelThree::w()
{
    // Create a new phaser above the neterprise and moving forward
    int x0,y0,mx,my;
    x0 = player_->pos().x() + (parent_->getEnterprise()->width()/2);
    y0 = player_->pos().y() - parent_->getRedPhaser()->height()-1;
    mx = parent_->getLevel3()->width();
    my = parent_->getLevel3()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,0,-15,mx,my,this);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelThree::a()
{
    // Create a new phaser to the left of the enterprise and moving to the left.
    int x0,y0,mx,my;
    x0 = player_->pos().x() - parent_->getRedPhaser()->height()-1;
    y0 = player_->pos().y() + (parent_->getEnterprise()->height()/2);
    mx = parent_->getLevel3()->width();
    my = parent_->getLevel3()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,-15,0,mx,my,this);
    aPhaser->rotate(-90);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelThree::d()
{
    int x0,y0,mx,my;
    x0 = player_->pos().x() + parent_->getEnterprise()->width() + parent_->getRedPhaser()->height()+1;
    y0 = player_->pos().y() + (parent_->getEnterprise()->height()/2);
    mx = parent_->getLevel3()->width();
    my = parent_->getLevel3()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,15,0,mx,my,this);
    aPhaser->rotate(90);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}

void LevelThree::x()
{
    int x0,y0,mx,my;
    x0 = player_->pos().x() + (parent_->getEnterprise()->width()/2);
    y0 = player_->pos().y() + parent_->getEnterprise()->height()+1;
    mx = parent_->getLevel3()->width();
    my = parent_->getLevel3()->height();
    Phaser* aPhaser = new Phaser(parent_->getRedPhaser(),x0,y0,0,15,mx,my,this);
    scene_->addItem(aPhaser);
    things_.push_back(aPhaser);
}


