#ifndef PHASER_H
#define PHASER_H

#include <QPixmap>

#include "thing.h"
#include "GameplayWindow.h"

class GameplayWindow;

/**This will implement a basic phaser that will continue in the x and y
* direction at constant velocity. The velocities cannot be changed once fired.
* @author Jacob Tucker */
class Phaser : public Thing {
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
    Phaser(QPixmap* mp, int nx, int ny, int vx, int vy, int maxX, int maxY, GameplayWindow* parent);
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
