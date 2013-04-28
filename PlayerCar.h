#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QRectF>

#include "thing.h"

/**This is the car that represents the player.*/
class PlayerCar : public Thing {
 public:
  /**Default constructor. All parameters are the same as the default constructor of the Thing class.*/
  PlayerCar(QPixmap* mp, int nx, int ny);
  void move();
  /**Increases the value of acceleration in the Y direction by 1 (technically negative 1 because this makes it move up the screen)*/
  void incrementAccel();
  /**Decreases the value of acceleration in the Y direction by 1 (technically it increases it by 1 because of the reversed directions as explained under @see incrementAccel*/
  void decrementAccel();
  /**Makes the car swerve.*/
  void swerve();
  /**Throws out the steering wheel. All this function really does is sets the acceleration to be 2 in the y direction and 0 in the x direction. It also locks out the increment and decrement functions*/
  void throwWheel();
  /**This should be called to indicate to the car that it should not move. The controlls are also locked out and it is impossible to accellerate in any direction.*/
  void stop_moving();
  

 private:
  int aX;
  int aY;
  int counter;
  bool swerve_;
  bool throwWheel_;
  bool allStop_;
};

#endif
