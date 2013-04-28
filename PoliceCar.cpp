#include "PoliceCar.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

PoliceCar::PoliceCar(QPixmap* mp, int nx, int ny) : Thing(mp, nx, ny)
{
  computerSide = false;
  moving = false;
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

void PoliceCar::swerve(int y1, int x1)
{
  rotate(25);
  const int t = 10;
  aY = (2*(y1-(vY*t)-pos().y()))/(t*t);
  aX = (2*(x1-pos().x()))/(t*t);
}

void PoliceCar::move()
{
  // We want to let the player's car get a head start.
  if (moving && counter > 5) {
    vX = vX + aX;
    vY = vY + aY;
  }
  //std::cout << "(" << vX << "," << vY << ")" << std::endl;
  setPos(pos().x() + vX, pos().y() + vY);
  counter++;
}

bool PoliceCar::is_moving()
{
  return moving;
}
