#include "ComputerCar.h"
#include "math.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

// S100 means it definitely won't swerve.
// S75 means 75% chance of swerving
// S25 means 25% chance of swerving
// RANDOM means 50% chance of swerving
// FAKE means definitely won't swerve, but will fake it first
// THROWSW means definitely won't swerve and will throw out the steering wheel
enum {RANDOM,S75,S25,THROWSW,S100,FAKE};

ComputerCar::ComputerCar(QPixmap* mp, int nx, int ny, int ph, GameplayWindow* parent) : Thing(mp, nx, ny)
{
  defSwerve = false;
  swerve = false;
  parent_ = parent;
  fakeCount = 0;

  // Create the strategies array
  int strategies[6] = {RANDOM,S75,S25,THROWSW,S100,FAKE};
  
  rotate(180);
  counter_ = 0;
  accel = false;
  aX = 0;
  aY = 0;
  
  // Pick a strategy
  int selection = rand() % 6;
  strat = strategies[selection];
  
  // Pick a swerve location
  swerveLoc = rand() % static_cast<int>(2*sqrt((744-ph-mp->height())/2));
  swerveLoc = swerveLoc + 10;
}

void ComputerCar::move()
{
  if (vY <= 0) {
    aY = 0;
    vY = 0;
  }
  if (swerve && counter_ > swerveLoc + 30) {
    vX = 0;
    vY = 0;
    aX = 0;
    aY = 0;
  }
  if (counter_ == 10) {
    accel = true;
    aX = 0;
    aY = 1;
  }
  setPos(pos().x()+vX,pos().y()+vY);
  if (accel) {
    vX = vX+aX;
    vY = vY+aY;
  }
  
  //This first one is for testing purposes
  if (defSwerve && counter_ == swerveLoc+10) {
    rotate(270);
    QRectF myRect = boundingRect();
    setPos(pos().x()+myRect.height(),pos().y());
    aX = 1;
    aY = -10;
    swerve = true;
  } else if (strat == RANDOM && counter_ == swerveLoc+10) {
    srand( time(NULL) );
    int decide = rand() % 2;
    if (decide == 0) {
      rotate(270);
      QRectF myRect = boundingRect();
      setPos(pos().x()+myRect.height(),pos().y());
      aX = 1;
      aY = -10;
      swerve = true;
    }
  } else if (strat == S75 && counter_ == swerveLoc) {
    srand( time(NULL) );
    int decide = rand() % 4;
    if (decide == 0 || decide == 1 || decide == 2) {
      rotate(270);
      QRectF myRect = boundingRect();
      setPos(pos().x()+myRect.height(),pos().y());
      aX = 1;
      aY = -10;
      swerve = true;
    }
  } else if (strat == S25 && counter_ == swerveLoc) {
    srand( time(NULL) );
    int decide = rand() % 4;
    if (decide == 1) {
      rotate(270);
      QRectF myRect = boundingRect();
      setPos(pos().x()+myRect.height(),pos().y());
      aX = 1;
      aY = -10;
      swerve = true;
    }
  } else if (strat == THROWSW && counter_ == swerveLoc) {
    parent_->computerThrowWheel();
  } else if (strat == THROWSW && counter_ == swerveLoc) {
    if (fakeCount == 0) {
      aX = 1;
      aY = -1;
      swerveLoc = swerveLoc + 10;
      fakeCount++;
    } else if (fakeCount == 1) {
      aX = -1;
      aY = 1;
      swerveLoc = swerveLoc + 10;
      fakeCount++;
    } else {
      aX = 0;
    }
  }
  
  counter_++;
}

void ComputerCar::setDefSwerve(bool s)
{
  defSwerve = s;
}
