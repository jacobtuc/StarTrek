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
                    parent_->changeScore(10);
                    decreaseWarbirdHealth();
                    return;
                }
                if (wThing && pThing1)
                {
                    //A phaser has hit the warbird
                    removeThing(pThing1);
                    parent_->changeScore(10);
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
    playerHealth = 100;

    // Create the enterprise
    player_ = new Enterprise(parent_->getEnterprise(),0,parent_->getLevel3()->height() - parent_->getEnterprise()->height());
    scene_->addItem(player_);
    things_.push_back(player_);
    borgTargets_.push_back(player_);

    // Create the borg
    int xb0 = (parent_->getLevel3()->width()/2) - (parent_->getBorg()->width()/2);
    int yb0 = (parent_->getLevel3()->height()/2) - (parent_->getBorg()->height()/2);
    int mx = parent_->getLevel3()->width();
    int my = parent_->getLevel3()->height();
    borg_ = new Borg(parent_->getBorg(),xb0,yb0,mx,my);
    scene_->addItem(borg_);
    things_.push_back(borg_);

    // Create the first three ships of the fleet
    int fleetSize;
    QPixmap** fleet = parent_->getFleet(fleetSize);
    for (int n = 0; n < 3; n++) {
        // Pick the pixmap
        srand(time(NULL)+n);
        FleetShip* aShip = new FleetShip(fleet[rand() % fleetSize],parent_->getLevel3()->width(),parent_->getLevel3()->height(),n*9,this);
        scene_->addItem(aShip);
        things_.push_back(aShip);
        borgTargets_.push_back(aShip);
    }

    counter = 0;
    borgNextFire = 20;
    nextMine = 40;
    nextTorpedo = 40;
    createShip = 0;
    timer_ = new QTimer(this);
    timer_->setInterval(50);
    connect(timer_,SIGNAL(timeout()),this,SLOT(handleTimer()));
    timer_->start();
}

void LevelThree::removeThing(Thing* item)
{
    //std::cout << "removing thing " << item << std::endl;
    //Remove the thing from the vector
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it) {
        if (*it == NULL)
            break;
        if (*it == item) {
            // Check to see if it is being targeted, and remove those things too
            int targSize = (*it)->getTargetedBy().size();
            if (targSize != 0)
            {
                //std::cout << "Checking targeted by list" << std::endl;
                std::vector<Thing*>::iterator itt;
                for (itt = (*it)->getTargetedBy().begin(); itt != (*it)->getTargetedBy().end(); ++itt) {
                    //std::cout << "  Removing a thing" << std::endl;
                    removeThing(*itt);
                }
                //std::cout << "  Clearing targeted by list" << std::endl;
                (*it)->getTargetedBy().clear();
            }
            things_.erase(it);
            scene_->removeItem(item);
            break;
        }
    }
    //std::cout << "Removed thing" << std::endl;
}

void LevelThree::removeFleetShip(Thing* item)
{
    //std::cout << "Removing fleet ship" << std::endl;
    std::vector<Thing*>::iterator it;
    for (it = things_.begin(); it != things_.end(); ++it)
    {
        if (*it == NULL)
            break;
        if (*it == item)
        {
            int targSize = (*it)->getTargetedBy().size();
            if (targSize != 0) {
                // Check to see if it is being targeted, and remove those things too
                //std::cout << "Checking targeted by list" << std::endl;
                std::vector<Thing*>::iterator itt;
                for (itt = (*it)->getTargetedBy().begin(); itt != (*it)->getTargetedBy().end(); ++itt) {
                    //IT will never be a fleet ship, so we can just call the normal remove function.
                    if (*itt == NULL)
                        break;
                    removeThing(*itt);
                }
                //std::cout << "clearing targeted by list" << std::endl;
                (*it)->getTargetedBy().clear();
            }//End targeted by check
            //std::cout << "removing from things list" << std::endl;
            things_.erase(it);
            //std::cout << "removing from scene" << std::endl;
            scene_->removeItem(item);
            break;
        }
    }

    // Remove from the target list as well
    for (it = borgTargets_.begin(); it != borgTargets_.end(); ++it)
    {
        if (*it == NULL) break;
        if (*it == item)
        {
            borgTargets_.erase(it);
            break;
        }
    }
    //std::cout << "Removed fleet ship" << std::endl;
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
    if (counter == borgNextFire)
    {
        // Borg should fire a phaser
        int bSize = borgTargets_.size();
        int targ = rand() % bSize;

        int pVX,pVY,xd,yd,x0,y0;
        Thing* target = borgTargets_[targ];

        xd = target->pos().x();
        yd = target->pos().y();
        x0 = (parent_->getLevel3()->width()/2) - (parent_->getGreenPhaser()->width()/2);
        y0 = (parent_->getLevel3()->height()/2) - (parent_->getGreenPhaser()->height()/2);

        int numerator = ((xd-x0)*(xd-x0)) + ((yd-y0)*(yd-y0));
        int velMax = 15;
        int velMaxSq = velMax*velMax;
        int t = static_cast<int>(sqrt(numerator/velMaxSq));

        if (t == 0)
        {
            pVX = 0;
            pVY = 0;
        } else {
            pVX = (xd-x0)/t;
            pVY = (yd-y0)/t;
        }

        BorgPhaser* aPhaser = new BorgPhaser(parent_->getGreenPhaser(),x0,y0,pVX,pVY,parent_->getLevel3()->width(),parent_->getLevel3()->height(),this);
        scene_->addItem(aPhaser);
        things_.push_back(aPhaser);
        /*
        if (target->pos().x() < borg_->pos().x())
        {
            // The player is to the left of the warbird
            if (target->pos().y() < borg_->pos().y())
            {
                // The player is to the left and above the warbird
                x0 = borg_->pos().x()-borg_->getPixmap()->width()-1-parent_->getGreenPhaser()->width();
                y0 = borg_->pos().y() - borg_->getPixmap()->height() - 1-parent_->getGreenPhaser()->height();
            } else {
                // The player is to the left and below the warbird
                x0 = borg_->pos().x()-borg_->getPixmap()->width()-1-parent_->getGreenPhaser()->width();
                y0 = borg_->pos().y() +1;
            }
        } else {
            // The player is to the right of the warbird
            if (target->pos().y() < borg_->pos().y()) {
                // The player is to the right and above the warbird
                x0 = borg_->pos().x()+1;
                y0 = borg_->pos().y()-borg_->getPixmap()->height()-1-parent_->getGreenPhaser()->height();
            } else {
                // THe player is to the right and below the warbird
                x0 = borg_->pos().x()+1;
                y0 = borg_->pos().y()+1;
            }
        }

        // We want the total velocity to be 15, so we have to calculate based on the velocity constraint
        xd = target->pos().x()+(parent_->getBorg()->width()/2);
        yd = target->pos().y()+(parent_->getBorg()->height()/2);
        int numerator = ((xd-x0)*(xd-x0)) + ((yd - y0)*(yd-y0));
        int t = static_cast<int>(sqrt(numerator/225));
        if (t != 0) {
            pVX = (xd-x0)/t;
            pVY = (yd-y0)/t;
            BorgPhaser* aPhaser = new BorgPhaser(parent_->getGreenPhaser(),x0,y0,pVX,pVY,parent_->getLevel3()->width(),parent_->getLevel3()->height(),this);
            scene_->addItem(aPhaser);
            things_.push_back(aPhaser);
        } */

        // Reset the nextFire number
        borgNextFire = 2;
        borgNextFire = borgNextFire + counter + 1;
    }// End borg fire

    if (counter == createShip)
    {
        int fleetSize;
        QPixmap** fleet = parent_->getFleet(fleetSize);

        srand(time(NULL)+counter);
        FleetShip* aShip = new FleetShip(fleet[rand() % fleetSize],parent_->getLevel3()->width(),parent_->getLevel3()->height(),counter*3,this);
        scene_->addItem(aShip);
        things_.push_back(aShip);
        borgTargets_.push_back(aShip);

        createShip = rand() % 60;
        createShip = createShip + counter + 1;
    } // End create ship

    if (counter == nextTorpedo)
    {
        //std::cout << "Creating torpedo" << std::endl;
        // Select the target
        int selSize = borgTargets_.size();
        srand(time(NULL));
        int target = rand() % selSize;
        int nx = (parent_->getLevel3()->width()/2) - (borgTargets_[target]->getPixmap()->width()/2);
        int ny = (parent_->getLevel3()->height()/2) - (borgTargets_[target]->getPixmap()->height()/2);
        Torpedo* aTorpedo = new Torpedo(parent_->getTorpedo(),nx,ny,borgTargets_[target]);
        borgTargets_[target]->setTargetedBy(aTorpedo);
        scene_->addItem(aTorpedo);
        things_.push_back(aTorpedo);

        // Reset the timing stuff
        int nT = rand() % 30 + 1;
        nextTorpedo = counter + nT;
        //std::cout << "Torpedo created" << std::endl;
    } //End torpedo

    if (counter == nextMine)
    {
        //std::cout << "Creating mine" << std::endl;
        Mine* aMine = new Mine(parent_->getMine(),borg_->pos().x(),borg_->pos().y(),borg_->getPixmap()->width(),borg_->getPixmap()->height(),parent_->getLevel3()->width(),parent_->getLevel3()->height());
        scene_->addItem(aMine);
        things_.push_back(aMine);

        // Reset the timing stuff
        int nM = rand() % 30 + 1;
        nextMine = nM + counter;
        //std::cout << "Mine created" << std::endl;
    } //End mine
    // Moe all the things
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
        things_[n]->move();

    // Toggle the timer counter
    counter++;

    // Check collisions
    handleCollisions();
}

void LevelThree::handleCollisions()
{
    int tSize = things_.size();
    for (int n = 0; n < tSize; n++)
    {
        for (int i = 0; i < tSize; i++)
        {
            if (n == i) // An object will always be colliding with itself
                continue;
            if (things_[n]->collidesWithItem(things_[i]))
            {
                //std::cout << "Handling a collision" << std::endl;
                Enterprise* eThing = dynamic_cast<Enterprise*>(things_[n]);
                Borg* bThing = dynamic_cast<Borg*>(things_[n]);
                FedPhaser* fpThing = dynamic_cast<FedPhaser*>(things_[n]);
                Phaser* pThing = dynamic_cast<Phaser*>(things_[n]);
                BorgPhaser* bpThing = dynamic_cast<BorgPhaser*>(things_[n]);
                FleetShip* fThing = dynamic_cast<FleetShip*>(things_[n]);
                Torpedo* tThing = dynamic_cast<Torpedo*>(things_[n]);
                Mine* mThing = dynamic_cast<Mine*>(things_[n]);

                Enterprise* eThing1 = dynamic_cast<Enterprise*>(things_[i]);
                Phaser* pThing1 = dynamic_cast<Phaser*>(things_[i]);
                BorgPhaser* bpThing1 = dynamic_cast<BorgPhaser*>(things_[i]);
                FleetShip* fThing1 = dynamic_cast<FleetShip*>(things_[i]);
                Borg* bThing1 = dynamic_cast<Borg*>(things_[i]);
                FedPhaser* fpThing1 = dynamic_cast<FedPhaser*>(things_[i]);
                Torpedo* tThing1 = dynamic_cast<Torpedo*>(things_[i]);
                Mine* mThing1 = dynamic_cast<Mine*>(things_[i]);

                //std::cout << "  Checking items" << std::endl;
                if (eThing && bpThing1)
                {
                    // The enterprise is colliding with a borg phaser
                    decreaseEnterpriseHealth();
                    removeThing(bpThing1);
                    handleCollisions();
                    return;
                }
                //std::cout << "Checking eThing1 and bpThing" << std::endl;
                if (eThing1 && bpThing)
                {
                    // The enterprise has been hit by a borg phaser
                    decreaseEnterpriseHealth();
                    removeThing(bpThing);
                    handleCollisions();
                    return;
                }
                //std::cout << "Checking eThing and bThing1" << std::endl;
                if (eThing && bThing1)
                {
                    // The enterprise has collided with the borg ship
                    parent_->changeScore(100);
                    newLevel();
                    parent_->loseLife();
                    handleCollisions();
                    return;
                }

                //std::cout << "checking eThing1 and bThing" << std::endl;

                if (eThing1 && bThing)
                {
                    // The enterprise has collided with the borg ship
                    parent_->changeScore(100);
                    newLevel();
                    parent_->loseLife();
                    handleCollisions();
                    return;
                }

                //std::cout << "cheking bThing and fpThing1" << std::endl;

                if (bThing && fpThing1)
                {
                    //A non player member of the fleet has hit the borg
                    removeThing(fpThing1);
                    handleCollisions();
                    return;
                }

                //std::cout << "checking bThing1 and fpThing" << std::endl;
                if (bThing1 && fpThing)
                {
                    //A non player member of the fleet has hit the borg
                    removeThing(fpThing);
                    handleCollisions();
                    return;
                }

                //std::cout << "checking bThing and pThing1" << std::endl;

                if (bThing && pThing1)
                {
                    // The player has hit the borg with a phaser
                    parent_->changeScore(10);
                    removeThing(pThing1);
                    handleCollisions();
                    return;
                }

                //std::cout << "checking bThing1 and pThing" << std::endl;

                if (bThing1 && pThing)
                {
                    // The player has hit the borg with a phaser
                    parent_->changeScore(10);
                    removeThing(pThing);
                    handleCollisions();
                    return;
                }

               // std::cout << "checking bpThing and fThing1" << std::endl;

                if (bpThing && fThing1)
                {
                    // The borg has hit a member of the fleet with a phaser
                    fThing1->hit();
                    removeThing(bpThing);
                    handleCollisions();
                    return;
                }

                //std::cout << "checking bpThing1 and fThing" << std::endl;
                if (bpThing1 && fThing)
                {
                    //std::cout << "bpThing1 and fThing" << std::endl;
                    // The borg has hit a member of the fleet with a phaser
                    fThing->hit();
                    //std::cout << "removing thing bpThing1" << std::endl;
                    removeThing(bpThing1);
                    //std::cout << "done handling bpThing1 and fThing" << std::endl;
                    handleCollisions();
                    //std::cout << "End recursive for bpThing1 and fThing." << std::endl;
                    return;
                }

                //std::cout << "checking eThing and mThing1" << std::endl;
                if (eThing && mThing1)
                {
                    if (mThing1->moving())
                        break;
                    //std::cout << "Enterprise hit a mine" << std::endl;
                    // The enterprise has hit a mine
                    decreaseEnterpriseHealth(75);
                    removeThing(mThing1);
                    //std::cout << "Handled ething and mthing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from ething and mthing1" << std::endl;
                    return;
                }

                //std::cout << "checking eThing1 and mThing" << std::endl;
                if (eThing1 && mThing)
                {
                    if (mThing->moving())
                        break;
                    //std::cout << "Enterprise hit a mine" << std::endl;
                    // The enterprise has hit a mine
                    decreaseEnterpriseHealth(75);
                    removeThing(mThing);
                    //std::cout << "Handled ething1 and mthing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from ething1 and mthing" << std::endl;
                    return;
                }

                //std::cout << "checking pThing and mThing1" << std::endl;
                if (pThing && mThing1)
                {
                    if (mThing1->moving())
                        break;
                    //std::cout << "pThing and mThing1" << std::endl;
                    // The enterprise has shot a mine
                    parent_->changeScore(15);
                    removeThing(pThing);
                    removeThing(mThing1);
                    //std::cout << "Handled pThing and mThing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from pThing and mThing1" << std::endl;
                    return;
                }

               // std::cout << "checking pThing1 and mThing" << std::endl;
                if (pThing1 && mThing)
                {
                    if (mThing->moving())
                        break;
                    //std::cout << "pThing1 and mThing" << std::endl;
                    // The enterprise has shot a mine
                    parent_->changeScore(15);
                    removeThing(pThing1);
                    removeThing(mThing);
                    //std::cout << "Handled pThing1 and mThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from pThing1 and mThing" << std::endl;
                    return;
                }

                //std::cout << "checking fThing and mThing1" << std::endl;
                if (fThing && mThing1)
                {
                    if (mThing1->moving())
                        break;
                    // A fleet ship has hit a mine
                    fThing->mineHit();
                    removeThing(mThing1);
                    handleCollisions();
                    return;
                }

                //std::cout << "checking fThing1 and mThing" << std::endl;
                if (fThing1 && mThing)
                {
                    if (mThing->moving())
                        break;
                    //std::cout << "fThing1 and mThing" << std::endl;
                    // A fleet ship has hit a mine
                    fThing1->mineHit();
                    removeThing(mThing1);
                    //std::cout << "Handled fThing1 and mThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from fThing1 and mThing" << std::endl;
                    return;
                }

                //std::cout << "checking eThing and tThing1" << std::endl;
                if (eThing && tThing1 && (tThing1->getTarget() == eThing))
                {
                    //std::cout << "eThing and tThing1" << std::endl;
                    // A torpedo has hit the enterprise
                    decreaseEnterpriseHealth(50);
                    eThing->removeTargetedBy(tThing1);
                    removeThing(tThing1);
                    //std::cout << "Handled eThing and tThing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from eThing and tThing1" << std::endl;
                    return;
                }

                //std::cout << "checking eThing1 and tThing" << std::endl;
                if (eThing1 && tThing && (tThing->getTarget() == eThing1))
                {
                    //std::cout << "eThing1 and tThing" << std::endl;
                    // A torpedo has hit the enterprise
                    decreaseEnterpriseHealth(50);
                    eThing1->removeTargetedBy(tThing);
                    removeThing(tThing);
                    //std::cout << "Handled eThing1 and tThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from eThing1 and tThing" << std::endl;
                    return;
                }

                //std::cout << "checking fpThing and tThing1" << std::endl;
                if (fpThing && tThing1 && !tThing1->targetsPlayer())
                {
                    //std::cout << "fpThing and tThing1" << std::endl;
                    //A fed phaser has hit a torpedo that is targeting a member of the fleet that is not the player
                    removeThing(fpThing);
                    removeThing(tThing1);
                    //std::cout << "Handled fpThing and tThing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from fpThing and tThing1" << std::endl;
                    return;
                }

                //std::cout << "checking fpThing1 and tThing" << std::endl;
                if (fpThing1 && tThing && !tThing->targetsPlayer())
                {
                    //std::cout << "fpThing1 and tThing" << std::endl;
                    removeThing(fpThing1);
                    removeThing(tThing);
                    //std::cout << "Handled fpThing1 and tThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from fpThing1 and tThing" << std::endl;
                    return;
                }

                //std::cout << "checking pThing and tThing1" << std::endl;
                if (pThing && tThing1)
                {
                    //std::cout << "pThing and tThing1" << std::endl;
                    // The player has hit a torpedo
                    parent_->changeScore(20);
                    removeThing(pThing);
                    removeThing(tThing1);
                    //std::cout << "Handled pThing and tThing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from pThing and tThing1" << std::endl;
                    return;
                }
                //std::cout << "checking pThing1 and tThing" << std::endl;
                if (pThing1 && tThing)
                {
                    //std::cout << "pThing1 and tThing" << std::endl;
                    parent_->changeScore(20);
                    removeThing(pThing1);
                    removeThing(tThing);
                    //std::cout << "Handled pThing1 and tThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from pThing1 and tThing" << std::endl;
                    return;
                }
                //std::cout << "checking fThing and tThing1" << std::endl;
                if (fThing && tThing1 && (tThing1->getTarget() == fThing))
                {
                    //std::cout << "fThing and tThing1" << std::endl;
                    fThing->torpedoHit();
                    //std::cout << "removing targeted by" << std::endl;
                    fThing->removeTargetedBy(tThing1);
                    //std::cout << "removing tthing1" << std::endl;
                    removeThing(tThing1);
                    //std::cout << "Handled fThing and tThing1" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from fThing and tThing1" << std::endl;
                    return;
                }
                //std::cout << "fThing1 and tThing" << std::endl;
                if (fThing1 && tThing && (tThing->getTarget() == fThing1))
                {
                    //std::cout << "fThing1 and tThing" << std::endl;
                    fThing1->torpedoHit();
                    fThing1->removeTargetedBy(tThing1);
                    removeThing(tThing);
                    //std::cout << "Handled fThing1 and tThing" << std::endl;
                    handleCollisions();
                    //std::cout << "Ended recursive call from fThing1 and tThing" << std::endl;
                    return;
                }
                //std::cout << "End handle collision" << std::endl;
            }//End does collide if
        }//End inner-for loop
    }//End main for loop
}

void LevelThree::firePhaser(Thing* origin)
{
    // Create the romulan phaser
    int pVX,pVY,xd,yd,x0,y0;
    if (borg_->pos().x() < origin->pos().x())
    {
        // The player is to the left of the warbird
        if (borg_->pos().y() < origin->pos().y())
        {
            // The player is to the left and above the warbird
            x0 = origin->pos().x()-origin->getPixmap()->width()-1-parent_->getRedPhaser()->width();
            y0 = origin->pos().y() - origin->getPixmap()->height() - 1-parent_->getRedPhaser()->height();
        } else {
            // The player is to the left and below the warbird
            x0 = origin->pos().x()-origin->getPixmap()->width()-1-parent_->getRedPhaser()->width();
            y0 = origin->pos().y() +1;
        }
    } else {
        // The player is to the right of the warbird
        if (borg_->pos().y() < origin->pos().y()) {
            // The player is to the right and above the warbird
            x0 = origin->pos().x()+1;
            y0 = origin->pos().y()-origin->getPixmap()->height()-1-parent_->getRedPhaser()->height();
        } else {
            // THe player is to the right and below the warbird
            x0 = origin->pos().x()+1;
            y0 = origin->pos().y()+1;
        }
    }

    // We want the total velocity to be 15, so we have to calculate based on the velocity constraint
    xd = borg_->pos().x()+(parent_->getBorg()->width()/2);
    yd = borg_->pos().y()+(parent_->getBorg()->height()/2);
    int numerator = ((xd-x0)*(xd-x0)) + ((yd - y0)*(yd-y0));
    int t = static_cast<int>(sqrt(numerator/225));
    if (t != 0) {
        pVX = (xd-x0)/t;
        pVY = (yd-y0)/t;
        FedPhaser* aPhaser = new FedPhaser(parent_->getRedPhaser(),x0,y0,pVX,pVY,parent_->getLevel3()->width(),parent_->getLevel3()->height(),this);
        scene_->addItem(aPhaser);
        things_.push_back(aPhaser);
    }
}

void LevelThree::pause()
{
    timer_->stop();
}

void LevelThree::restart()
{
    timer_->start();
}

void LevelThree::newLevel()
{
    player_->setPos(0,parent_->getLevel3()->height()-parent_->getEnterprise()->height());
    parent_->loseLife();
}
void LevelThree::decreaseEnterpriseHealth()
{
    playerHealth = playerHealth - 20;

    if (playerHealth <= 0)
        newLevel();
}

void LevelThree::decreaseEnterpriseHealth(int dS)
{
    playerHealth = playerHealth - dS;

    if (playerHealth <= 0)
        newLevel();
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


