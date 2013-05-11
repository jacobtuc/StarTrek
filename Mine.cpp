#include "Mine.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Mine::Mine(QPixmap* mp, int bx, int by, int bw, int bh, int sw, int sh) : Thing(mp,bx+(bw/2),by+(bh/2))
{
    moving_ = true;
    counter_ = 0;
    // We'll separate the screen into four areas where the
    // mine could be laid.
    // We'll keep track of it with variables for the minimum x and
    // y locations of the selected area.
    srand(time(NULL));
    int rectSelect = rand() % 4;

    int minX,minY,maxX,maxY;

    if (rectSelect == 0)
    {
        // Left box
        minX = 0;
        minY = 0;
        maxX = (sw/2)-(bw/2);
        maxY = (sh/2)+(bh/2);
    } else if (rectSelect == 1)
    {
        // Top box
        minY = 0;
        minX = (sw/2)-(bw/2);
        maxX = sw-mp->width();
        maxY = (sh/2)-(bh/2);
    } else if (rectSelect == 2)
    {
        // Right box
        minY = (sh/2)-(bh/2);
        minX = (sw/2)+(bw/2);
        maxX = sw-mp->width();
        maxY = sh-mp->height();
    } else if (rectSelect == 3)
    {
        // Bottom box
        minX = 0;
        minY = (sh/2)+(bh/2);
        maxX = (sw/2)+(bw/2);
        maxY = sh-mp->height();
    } else {
        maxX = 1000;
        maxY = 500;
        minX = 0;
        minY = 0;
    }

    // Select the position within those constraints
    int dx = rand() % maxX + minX;
    int dy = rand() % maxY + minY;

    vX = (dx-pos().x())/30;
    vY = (dy-pos().y())/30;
}

void Mine::move()
{
    if (counter_ == 30)
    {
        vX = 0;
        vY = 0;
        moving_ = false;
    }
    setPos(pos().x() + vX, pos().y() + vY);
    counter_++;
}

bool Mine::moving()
{
    return moving_;
}
