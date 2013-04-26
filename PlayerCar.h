#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "thing.h"

/**This is the car that represents the player.*/
class PlayerCar : public Thing {
 public:
  PlayerCar(QPixmap* mp, int nx, int ny);
  void move();
};

#endif
