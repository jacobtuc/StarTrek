#include "Asteroid.h"
#include <stdlib.h>
#include <time.h>

Asteroid::Asteroid(QPixmap* mp, int mainWidth, int seed) : Thing(mp, 0, 0)
{
    srand(seed);
    int xLoc = rand() % mainWidth;
    setPos(xLoc,0);

    // Velocity should be constant and selected randomly
    vY = rand() % 15 + 5;
}

void Asteroid::move()
{
    setPos(pos().x() + vX, pos().y() + vY);
}
