#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <vector>

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
  /**Returns a pointer to the pixmap of the Thing*/
  QPixmap* getPixmap() const;
  /**Adds the given thing to the array of things this thing is
  * being targeted by so they can be removed when the object is deleted.
  * @param targetedBy The thing that is now targeting this thing.*/
  void setTargetedBy(Thing* targetedBy);
  /**Retrieves the vector that stores a list of pointers of what this thing
  * is being targeted by so they can be deleted along with this thing.*/
  std::vector<Thing*>& getTargetedBy();
  /**Removes the given thing from the targeted by list. This should be called
  * when the object is being destroyed by a phaser.
  * @param targetedBy The thing to be removed from the list. If it's not in the list, nothing will happen.*/
  void removeTargetedBy(Thing* targetedBy);

 protected:
  int vX;
  int vY;
  QPixmap* myPix;
  std::vector<Thing*> targetedBy_;

};

#endif
