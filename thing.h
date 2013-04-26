#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

/**Thing is a virtual class that represents any moving pixmap object.*/
class Thing : public QGraphicsPixmapItem {
 public:
  /**The default constructor
     @param mp The pixmap to be placed on the item
     @param nx The position on the x axis in the scene where the thing should be placed
     @param ny The position on the y axis in the scene where the thing should be placed
     @post As implemented in this virtual class, the x and y positions are set with their corresponding local variables. The pixmap is loaded, placed on the item, and the myPix private variable is set to the address of mp.
  */
  Thing(QPixmap* mp, int nx, int ny);
  /**This function should move the object by one tick (one call of the timer handler) as per the x and y velocities*/
  virtual void move() = 0;
  /**Sets the x and y velocities
     @param nx The new x velocity in pixels per 100 miliseconds
     @param ny The new y velocity in pixels per 100 miliseconds
  */
  void setVelocity(int nx, int ny);
  /**Returns the current value of the velocity in the x direction*/
  int getVelocityX();
  /**Returns the current value of the velocity in the y direction*/
  int getVelocityY();

 protected:
  int vX;
  int vY;
  QPixmap* myPix;

};

#endif
