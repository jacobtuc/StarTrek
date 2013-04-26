#ifndef TUMBLEWEED_H
#define TUMBLEWEED_H

#include "thing.h"

/**This is the tumbleweed that will block the player's view if it hits them.*/
class Tumbleweed : public Thing {
 public:
  /**Default construct. All parameters are identical to the Thing constructor except for the listed exceptions.
   * @param pw The width of the player's car. This is used to calculate accelleration so the car and the tumbleweed will collide if the player continues to accelerate.
   * @param ph The height of the player's car. This is used to calculate accelleration so the car and the tumbleweed will collide if the player continues to accellerate. */
  Tumbleweed(QPixmap* mp, int nx, int ny, int pw, int ph);
  void move();

 private:
  int aX;
  int aY;
  bool moving;
};
#endif
