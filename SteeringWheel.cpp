#include "SteeringWheel.h"

SteeringWheel::SteeringWheel(QPixmap* mp, int nx, int ny, int vy) : Thing(mp, nx, ny)
{
  counter = 0;
  aY = -2;
  vY = vy;
  vX = vY;
  aX = -2;
  
}

void SteeringWheel::move()
{
  if (counter == 50) {
    aX = 0;
    aY = 0;
    vX = 0;
    vY = 0;
  }
  vX = vX + aX;
  vY = vY + aY;
  setPos(pos().x()+vX,pos().y()+vY);
  counter++;
}
