#ifndef BORGPHASER_H
#define BORGPHASER_H

#include "thing.h"
#include "GameplayWindow.h"

class GameplayWindow;

/**This class has all the same properties as a nomral phaser
* but is implemented seperately so collision testing can be
* done for level three. This phaser should only be shot by
* the borg ship. All other ships should use the normal Phaser
* class.
* @author Jacob Tucker
* @see Phaser*/
class BorgPhaser : public Thing {
public:
    /**Default constructor
    * @param mp The pixmap to be loaded. This should be one of the phasers from the main window.
    * @param nx The initial x position of the phaser.
    * @param ny The initial y position of the phaser.
    * @param vx The initial velocity in the x position. This cannot be changed later.
    * @param vy The initial velocity in the y position. This cannot be changed later.
    * @param maxX The width of the landscape
    * @param maxY The height of the landscape
    */
    BorgPhaser(QPixmap* mp, int nx, int ny, int vx, int vy, int maxX, int maxY, GameplayWindow* parent);
    /**The requisite move function to be called by the timer.*/
    void move();
    /**Overloads the set velocity function of the thing class to prevent changes in the x and y velocities.*/
    void setVelocity(int nx, int ny);

private:
    int mx;
    int my;
    QPixmap* image;
    bool removing;
    GameplayWindow* parent_;
};


#endif
