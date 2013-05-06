#ifndef ASTEROID_H
#define ASTEROID_H

#include <QPixmap>

#include "thing.h"

/**This is the asteroid that will appear at the top of the screen and
* move straight down. The player will have to avoid and/or destroy these
* asteroids. Their velocity will be constant in the y direction and they
* should be destroyed when they reach the end of the screen.
* @author Jacob Tucker */
class Asteroid : public Thing {
public:
    /**Default constructor
    * @param mp The pixmap to be loaded on the object. Same as the Thing constructor.
    * @param mainWidth The width of the graphics window. This is used to decide the initial x position of the object.
    * @param seed The seed for the random number generator to pick the x position of the asteroid
    */
    Asteroid(QPixmap* mp, int mainWidth, int seed);
    /**The move function of the object. It moves down as per the y velocity that will be selected randomly between 5 and 15.*/
    void move();
};

#endif
