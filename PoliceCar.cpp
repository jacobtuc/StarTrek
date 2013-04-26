#include "PoliceCar.h"

PoliceCar::PoliceCar(QPixmap* mp, int nx, int ny) : Thing(mp, nx, ny)
{
  computerSide = false;
  if (ny == 0) {
    rotate(180);
    computerSide = true;
  }
  
  // Set the accellerations
  aY = 1;
  aX = 0;
}

void PoliceCar::move()
{
  setPos(pos().x() + vX, pos().y() + vY);
}
