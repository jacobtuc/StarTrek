#ifndef COMPUTERCAR_H
#define COMPUTERCAR_H

#include <QPixmap>

#include "thing.h"
#include "gameplay_window.h"

class GameplayWindow;

class ComputerCar : public Thing {
 public:
  /**Default constructor. Everythign is the same as the Thing constructor except the following:
   * @param ph The height of the player's car. This is necessary to calculate swerve locations.
   * @param parent The GameplayWindow that owns the object. This is neccessary for the steering wheel function. */
  ComputerCar(QPixmap* mp, int nx, int ny, int ph, GameplayWindow* parent);
  void move();
  /**Sets the definite swerve variable. This is meant for testing purposes to demonstrate the swervability of the computer car.
   * @param s True if you want the computer to swerve for sure. False if you want it to choose normally.
   */
  void setDefSwerve(bool s);

 private:
  GameplayWindow* parent_;
  int counter_;
  int aX;
  int aY;
  bool accel;
  int strat;
  int swerveLoc;
  bool fakeCount;
  bool defSwerve;
};

#endif
