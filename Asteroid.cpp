#include "Asteroid.h"
#include <stdlib.h>
#include <time.h>

Asteroid::Asteroid(QPixmap* mp, int mainWidth, int seed, int mx, int my, LevelOne* parent) : Thing(mp, 0, 0)
{
    parent_ = parent;
    image = mp;
    maxX = mx;
    maxY = my;
    removing = false;

    srand(seed);
    int xLoc = rand() % mainWidth;
    setPos(xLoc,0);

    // Velocity should be constant and selected randomly
    vY = rand() % 15 + 5;
}

void Asteroid::move()
{
    if (removing)
        return;
    if (pos().x() < 0-image->width() || pos().x() > maxX + 1 || pos().y() > maxY+1 || pos().y() < 0-image->height()) {
        removing = true;
        parent_->asteroidCleared();
        parent_->removeThing(this);
    }
    setPos(pos().x() + vX, pos().y() + vY);
}
