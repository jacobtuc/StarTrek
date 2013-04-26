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
  /**Increases the value of acceleration in the Y direction by 1 (technically negative 1 because this makes it move up the screen)*/
  void incrementAccel();
  /**Decreases the value of acceleration in the Y direction by 1 (technically it increases it by 1 because of the reversed directions as explained under @see incrementAccel*/
  void decrementAccel();
  /**Makes the car swerve.*/
  void swerve();

 private:
  int aX;
  int aY;
  int counter;
  bool swerve_;
};

#endif
