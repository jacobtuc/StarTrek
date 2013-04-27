#include "PoliceCar.h"
#include <stdlib.h>
#include <time.h>

PoliceCar::PoliceCar(QPixmap* mp, int nx, int ny) : Thing(mp, nx, ny)
{
  computerSide = false;
  if (ny == 0) {
    rotate(180);
    computerSide = true;
  }
  
  shouldMove = false;
  counter = 0;
  
  // Decide whether it's going to move
  srand( time(NULL) );
  int decision = rand() % 6; // Make it a 1/6 chance.
  if (decision == 3)
    shouldMove = true;
  // Set the accellerations
  aY = -1;
  aX = 0;
}

void PoliceCar::toggleMoving()
{
  if (shouldMove)
    moving = true;
  counter = 0;
}

void PoliceCar::setShouldMove(bool s)
{
  shouldMove = s;
}

void PoliceCar::swerve(int t)
{
  //TODO: Add code to make the police car end up at the same location as the player's car
  
}

void PoliceCar::move()
{
  // We want to let the player's car get a head start.
  if (moving && counter > 5) {
    vX = vX + aX;
    vY = vY + aY;
  }
  setPos(pos().x() + vX, pos().y() + vY);
  counter++;
}
