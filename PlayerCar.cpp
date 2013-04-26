#include "PlayerCar.h"

PlayerCar::PlayerCar(QPixmap* mp, int nx, int ny) : Thing(mp, nx, ny)
{
  
}

void PlayerCar::move()
{
  setPos(pos().x()+vX,pos().y()+vY);
}
