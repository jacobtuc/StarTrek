#include "FleetShip.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

FleetShip::FleetShip(QPixmap* mp, int mx, int my,int seed, LevelThree* parent) : Thing(mp,0,0)
{
    health = 100;
    parent_ = parent;
    // Select the position of the ship
    srand(time(NULL)+seed);
    seed_ = rand() % 2000;
    maxX = mx-mp->width();
    maxY = my-mp->height();
    int x0 = rand() % maxX;
    int y0 = rand() % maxY;
    setPos(x0,y0);

    counter = 0;
    nextMove = rand() % 20;
    vX = 0; vY = 0;
    targetTime = 0;
    phaserCount = 0;
}

void FleetShip::hit()
{
    health = health - 20;
    if (health <= 0)
    {
        parent_->removeFleetShip(this);
    }
}

void FleetShip::move()
{
    /*
    if (counter == nextMove)
    {
        // Needs to pick a new target location
        // Pick the x destination
        srand(time(NULL) + seed_);
        int xd = rand() % maxX;

        //Pick the y destination
        srand(time(NULL) + seed_*seed_ + 200);
        int yd = rand() % maxY;

        // Separating it makes the code prettier
        // We'll constrain total velocity to always be 10
        int xSide = xd - pos().x();
        int ySide = yd - pos().y();
        int numerator = (xSide*xSide) + (ySide*ySide);

        // Select a velocity
        srand(time(NULL) + counter*13);
        int vMax = rand() % 10;
        int vMaxSq = vMax*vMax;
        if (vMaxSq <= 0) {
            targetTime = 0;
        } else {
            targetTime = static_cast<int>(sqrt(numerator/vMaxSq));
        }
        if (targetTime <= 0)
        {
            vX = 0;
            vY = 0;
            targetTime = 0;
        } else {
            vX = (xd-pos().x())/targetTime;
            vY = (yd-pos().y())/targetTime;
        }

        targetTime = targetTime + counter;
    }
    if (counter == targetTime)
    {
        srand(time(NULL) + seed_);
        int myNextMove = rand() % 200;
        nextMove = counter + myNextMove;
        vX = 0; vY = 0;
    }

    setPos(pos().x() + vX, pos().y() + vY); */
    if (phaserCount == nextMove)
    {
        parent_->firePhaser(this);
        srand(time(NULL));
        nextMove = rand() % 35;
        phaserCount = 0;
    }
    if (counter == targetTime) {
        // Needs to pick a new target location
        // Pick the x destination
        srand(time(NULL)+seed_);
        int xd = rand() % maxX;

        //Pick the y destination
        srand(time(NULL) + counter + 200 + seed_);
        int yd = rand() % maxY;

        // Separating it makes the code prettier
        // We'll constrain total velocity to always be 10
        int xSide = xd - pos().x();
        int ySide = yd - pos().y();
        int numerator = (xSide*xSide) + (ySide*ySide);

        targetTime = static_cast<int>(sqrt(numerator/100));
        if (targetTime <= 0)
        {
            vX = 0;
            vY = 0;
            targetTime = 0;
        } else {
            vX = (xd-pos().x())/targetTime;
            vY = (yd-pos().y())/targetTime;
        }
        counter = 0;
    }
    setPos(pos().x()+vX,pos().y()+vY);
    counter++;
    phaserCount++;
}
