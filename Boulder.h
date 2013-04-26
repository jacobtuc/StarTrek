#ifndef BOULDER_H
#define BOULDER_H

#include "thing.h"

/**The boulder that will randomly begin rolling down the hill to hit the player's car if they do not slow down.*/
class Boulder : public Thing {
 public:
  /**Default constructor. All parameters are the same as the default thing constructor except the following exceptions:
   * @param playerHeight The height of the player car. This is used to calculate the acceleration of the boulder so it intercepts with the player car if they accelerate normally.*/
  Boulder(QPixmap* mp, int nx, int ny, int playerHeight);
  void move();

 private:
  int aX;
  int aY;
  bool moving;
};

#endif
