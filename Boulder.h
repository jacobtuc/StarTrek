#ifndef BOULDER_H
#define BOULDER_H

#include "thing.h"

/**The boulder that will randomly begin rolling down the hill to hit the player's car if they do not slow down. There is a 10% chance that the boulder will decide to move unless the value is manually set by the user (for testing purposes).*/
class Boulder : public Thing {
 public:
  /**Default constructor. All parameters are the same as the default thing constructor except the following exceptions:
   * @param playerHeight The height of the player car. This is used to calculate the acceleration of the boulder so it intercepts with the player car if they accelerate normally.*/
  Boulder(QPixmap* mp, int nx, int ny, int playerHeight);
  void move();
  /**This function should be called by the key press event for the up arrow(that starts the movement of the player's car). It will not automatically tell the boulder to move, but rather will start the movement if it had decided it was going to move in the constructor.*/
  void toggleMoving();
  /**This function is used for testing purposes. It allows the user to manually set the value of should move so they can force the boulder to move or to not move.
   * @param s True if you want the boulder to move. False otherwise.
   */
  void setShouldMove(bool s);

 private:
  int aX;
  int aY;
  bool moving;
  bool shouldMove;
};

#endif
