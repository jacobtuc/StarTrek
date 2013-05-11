#ifndef FLEETSHIP_H
#define FLEETSHIP_H

#include "thing.h"
#include "GameplayWindow.h"

class LevelThree;

/**This class represents a ship from the fleet. These should
* appear randomly and move randomly around the borg ship. The
* class can only be used from level three as it requires the
* fire phaser method that is only declared in level three.*/
class FleetShip : public Thing {
public:
    /**Default constructor. The first three parameters are the same as those of the Thing class.
    * @param mp The pixmap for the ship. This should be selected randomly.
    * @param mx The maximum x distance the ship can travel. This should be the width of the landscape for most implementations.
    * @param my The maximum y distance the ship can travel. This should be the width of the landscape for most implementations.
    * @param seed The number to be added to the time to create the seed for the random number generator. This should be unique to the rest of the fleet.
    * @param parent The level three window on which the ship is placed. This is used to fire phasers.*/
    FleetShip(QPixmap* mp, int mx, int my,int seed,LevelThree* parent);
    /**The requisite move function. This will implement the random movement of the ship.*/
    void move();
    /**Registers a hit to the ship. It will decrease health by 20 points and check to see if the ship
    * has been destroyed (whether health points are below zero) and call the proper remove function to
    * destroy itself if it has*/
    void hit();
    /**Registers a torpedo hitting the ship. It will decrease health by 50 points
    * and check to see if the ship has been destroyed (whether health points are below zero)
    * and call the proper remove function to destroy itself if it has.*/
    void torpedoHit();
    /**Registers a mine hitting the ship. It will descrease health by 75 points and check
    * to see if the ship has been destroyed (whether health points are below zero)
    * and call the proper remove function to destroy itself if it has.*/
    void mineHit();

private:
    int counter,phaserCount;
    // Next move is the next time the ship will fire a phaser
    int nextMove,targetTime;
    int maxX,maxY;
    int seed_;
    LevelThree* parent_;
    int health;
};

#endif
