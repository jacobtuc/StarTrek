#include "Tumbleweed.h"

Tumbleweed::Tumbleweed(QPixmap* mp, int nx, int ny, int pw, int ph) : Thing(mp, nx, ny)
{
  moving = false;
  aY = 0;
  aX = (pw+mp->width()-512.5)/(384.5-mp->height()-ph);
}

void Tumbleweed::move()
{
  setPos(pos().x()+vX,pos().y()+vY);
  if (moving) {
    vX = vX + aX;
    vY = vY + aY;
  }
}
