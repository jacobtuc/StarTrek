#include "Tumbleweed.h"
#include <stdlib.h>
#include <time.h>

Tumbleweed::Tumbleweed(QPixmap* mp, int nx, int ny, int pw, int ph) : Thing(mp, nx, ny)
{
  moving = false;
  shouldMove = false;
  defMove = false;
  srand( time(NULL) );
  int decision = rand() % 10;
  if (decision == 5)
    shouldMove = true;
  aY = 0;
  aX = (pw+mp->width()-512.5)/(384.5-mp->height()-ph);
}

void Tumbleweed::setShouldMove(bool s)
{
  shouldMove = s;
}

void Tumbleweed::toggleMoving()
{
  if (shouldMove)
    moving = true;
}

void Tumbleweed::move()
{
  setPos(pos().x()+vX,pos().y()+vY);
  if (moving) {
    vX = vX + aX;
    vY = vY + aY;
  }
}
