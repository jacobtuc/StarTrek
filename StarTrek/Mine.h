#ifndef MINE_H
#define MINE_H

#include "thing.h"

/**This is a mine laid by the borg ship. A ship should
* be destroyed if they collide with it. It will select
* location randomly that does not collide with the borg
* ship and should be destroyed upon collision with a phaser.
* @author Jacob Tucker*/
class Mine : public Thing {
public:
    /**Default constructor. It will select its own position.
    * @param mp The pixmap for the object. This should be retreived from MainWindow.
    * @param bx The x location of the borg ship
    * @param by The y location of the borg ship
    * @param bw The width of the borg ship
    * @param bh The height of the borg ship
    * @param sw The width of the landscape
    * @param sh The height of the landscape*/
    Mine(QPixmap* mp, int bx, int by, int bw, int bh, int sw, int sh);
    /**The requisite move function for thing objects.*/
    void move();
    /**Returns true of the objet is moving. The mine shouldn't be able
    * to collide with another object while it's moving. This should be
    * called by the collision handler.*/
    bool moving();

private:
    bool moving_;
    int counter_;
};

#endif
