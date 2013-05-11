#include "Borg.h"
#include <math.h>
#include <iostream>

Borg::Borg(QPixmap* mp, int nx, int ny, int mx, int my) : Thing(mp,nx,ny)
{
    maxX = mx-mp->width();
    maxY = my-mp->height();
    counter = 0;
    nextMove = 50;
    vX = 0; vY = 0;
    targetTime = 0;
}

void Borg::move()
{
    /*
    if (counter == nextMove)
    {
        // Needs to pick a new target location
        // Pick the x destination
        srand(time(NULL));
        int xd = rand() % maxX;

        //Pick the y destination
        srand(time(NULL) + counter + 200);
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
        int myNextMove = rand() % 200;
        nextMove = counter + myNextMove;
        vX = 0; vY = 0;
    } */

    setPos(pos().x() + vX, pos().y() + vY);
}
