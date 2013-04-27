#include "PlayerCar.h"

PlayerCar::PlayerCar(QPixmap* mp, int nx, int ny) : Thing(mp, nx, ny)
{
  aX = 0;
  aY = 0;
  swerve_ = false;
  throwWheel_ = false;
  counter = 0;
}



void PlayerCar::incrementAccel()
{
  if (swerve_ || throwWheel_)
    return;
  if (aY <= -1) {
    aY = -1;
    return;
  }
  aY = aY - 1;
}

void PlayerCar::swerve()
{
  rotate(90);
  QRectF myRect = boundingRect();
  setPos(pos().x()+myRect.height(),pos().y());
  aX = 10;
  aY = -5;
  swerve_ = true;
  counter = 0;
}

void PlayerCar::decrementAccel()
{
  if (swerve_ || throwWheel_)
    return;
  if (aY >= 2) {
    aY = 2;
    return;
  }
  aY = aY + 1;
}

void PlayerCar::throwWheel()
{
  aX = 0;
  aY = -2;
  vX = 0;
  throwWheel_ = true;
}

void PlayerCar::move()
{
  if (swerve_) {
    if (vY <= 0) {
      aY = 0;
      vY = 0;
    }
    if (counter > 30) {
      vX = 0;
      vY = 0;
      aX = 0;
      aY = 0;
    }
  }
  vX = vX+aX;
  vY = vY+aY;
  setPos(pos().x()+vX,pos().y()+vY);
  counter++;
}

