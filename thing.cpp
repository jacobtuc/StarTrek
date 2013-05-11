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

void Thing::setTargetedBy(Thing* targetedBy)
{
    targetedBy_.push_back(targetedBy);
}

std::vector<Thing*>& Thing::getTargetedBy()
{
    return targetedBy_;
}

void Thing::removeTargetedBy(Thing* targetedBy)
{
    std::vector<Thing*>::iterator it;
    for (it = targetedBy_.begin(); it != targetedBy_.end(); ++it) {
        if (*it == NULL)
            break;
        if (*it == targetedBy) {
            targetedBy_.erase(it);
            break;
        }
    }
}
