#ifndef POLICECAR_H
#define POLICECAR_H

#include "thing.h"

class PoliceCar : public Thing {
 public:
  PoliceCar(QPixmap* mp, int nx, int ny);
  void move();

 private:
  // Means that this is the police car on the side the computer car starts from
  bool computerSide;
  bool moving;
  int aX;
  int aY;
};
#endif
