#include "Enterprise.h"

Enterprise::Enterprise(QPixmap* mp, int nx, int ny) : Thing(mp,nx,ny)
{

}

Enterprise::~Enterprise()
{

}

void Enterprise::move()
{
    setPos(pos().x() + vX, pos().y() + vY);

    // The ship should only be moving while the key is being held, so we'll set these to zero after every move.
    vX = 0; vY = 0;
}
