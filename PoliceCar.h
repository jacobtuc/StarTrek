#ifndef POLICECAR_H
#define POLICECAR_H

#include <QPoint>

#include "thing.h"

/**As the name implies, this is a police car. If it intercepts (collides with) the player, the player loses a life and a significant amount of points. The police car will have a 1 in 6 chance of appearing and will not catch the player if they do not swerve.*/
class PoliceCar : public Thing {
 public:
  PoliceCar(QPixmap* mp, int nx, int ny);
  void move();
  /**This function should be called from the function that begins the accelleration of the player's car. If the police car decided to move, this will begin that motion. If it didn't, this will have no effect.*/
  void toggleMoving();
  /**This allows control for testing purposes. If s is true, the police car is guaranteed to show up.
   * @param s Set this as true if you definitely want the police car to show up. Set this to false if you changed your mind.*/
  void setShouldMove(bool s);
  /**This should be called from the function that makes the player's car swerve. This tells the police car to follow it so they collide.
   * @param yInt The Y position of the player's car when it swerved
   * @param x1 The x position where the players car will stop moving.
   */
  void swerve(int y1, int x1);
  /**Returns true if the police cr is moving. False otherwise.*/
  bool is_moving();

 private:
  // Means that this is the police car on the side the computer car starts from
  bool computerSide;
  bool moving;
  int counter;
  int aX;
  int aY;
  bool shouldMove;
};
#endif
