#ifndef STEERINGWHEEL_H
#define STEERINGWHEEL_H

#include <QPixmap>

#include "thing.h"

class SteeringWheel : public Thing {
 public:
  SteeringWheel(QPixmap* mp, int nx, int ny, int vy);
  void move();
  
 private:
  int counter;
  int aX;
  int aY;
};

#endif
