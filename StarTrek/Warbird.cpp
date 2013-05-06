#include "Warbird.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

Warbird::Warbird(QPixmap* mp, int nx, int ny, int maxX, int maxY) : Thing(mp,nx,ny)
{
    vX = 0;
    vY = 0;
    mx = maxX;
    my = maxY;
    counter = 0;
    targetTime = 0;
}

void Warbird::move()
{
    if (counter == targetTime) {
        // Needs to pick a new target location
        // Pick the x destination
        srand(time(NULL));
        int xd = rand() % mx;

        //Pick the y destination
        srand(time(NULL) + counter + 200);
        int yd = rand() % my;

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
}
