#ifndef TORPEDO_H
#define TORPEDO_H

#include "thing.h"
#include "Enterprise.h"

/**The torpedo to be launched by the borg ship.
* It has a player aware AI and will follow the
* player or another target until it has collided
* with it or been hit by a phaser from a player of
* the same type (ie if it is targeting the player,
* only the plaer can destroy it. If it is targeting
* a member of the fleet, only a phaser from the fleet
* can destroy it).
* @author Jacob Tucker*/
class Torpedo : public Thing {
public:
    /**Default constructor
    * @param mp The pixmap to be loaded onto the object
    * @param nx The initial x position. This should be the center of the borg ship
    * @param ny The initial y postion. This should be the center of the borg ship
    * @param target A pointer to the target.*/
    Torpedo(QPixmap* mp, int nx, int ny, Thing* target);
    /**Default destrucor.*/
    ~Torpedo();
    /**Requisite move function. This updates the velocity if the
    * target has moved.*/
    void move();
    /**Returns true if the torpedo is targeting the player. False if
    * it is targeting another member of the fleet.*/
    bool targetsPlayer();
    /** Returns a pointer to the thing the torpedo is targeting*/
    Thing* getTarget();

private:
    Thing* target_;
    bool playerTarget_;
};

#endif
