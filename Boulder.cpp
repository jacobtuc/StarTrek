#include "Boulder.h"

Boulder::Boulder(QPixmap* mp, int nx, int ny, int playerHeight) : Thing(mp, nx, ny)
{
  moving = false;
  // Add code to decide whether to move
  aY = 0;
  aX = (512.5-mp->width())/(384.5-(mp->height()/2)-playerHeight);
}

void Boulder::move()
{
  setPos(pos().x()+vX,pos().y()+vY);
  if (moving) {
    vX = vX + aX;
    vY = vY + aY;
  }
}
