#include "thing.h"

Thing::Thing(QPixmap* mp, int nx, int ny)
{
  vX = 0;
  vY = 0;
  myPix = mp;
  setPixmap(*myPix);
  setPos(nx,ny);
}

void Thing::setVelocity(int nx, int ny)
{
  vX = nx;
  vY = ny;
}

int Thing::getVelocityX()
{
  return vX;
}

int Thing::getVelocityY()
{
  return vY;
}

QPixmap* Thing::getPixmap() const
{
    return myPix;
}
