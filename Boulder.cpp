#include "Boulder.h"
#include <stdlib.h>
#include <time.h>

Boulder::Boulder(QPixmap* mp, int nx, int ny, int playerHeight) : Thing(mp, nx, ny)
{
  moving = false;
  shouldMove = false;
  srand( time(NULL) );
  int decision = rand() % 6;
  if (decision == 5)
    shouldMove = true;
  aY = 0;
  aX = (512.5-mp->width()+50)/(384.5-(mp->height()/2)-playerHeight);
}

void Boulder::setShouldMove(bool s)
{
  shouldMove = s;
}

void Boulder::toggleMoving()
{
  if(shouldMove)
    moving = true;
}

void Boulder::move()
{
  setPos(pos().x()+vX,pos().y()+vY);
  if (moving) {
    vX = vX + aX;
    vY = vY + aY;
  }
}
