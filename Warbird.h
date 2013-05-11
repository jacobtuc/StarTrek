#ifndef WARBIRD_H
#define WARBIRD_H

#include "thing.h"

/**This class is the romulan warbird. It will
* move randomly around the screen at changing velocities.
* @author Jacob Tucker */
class Warbird : public Thing {
public:
    /**Default Constructor - parameters are the same as the Thing class.
    * @param maxX The maximum position the warbird can move to on the x axis. This should be the width of the view for most implementations.
    * @param maxY THe maximum position the warbird can move to on the y axis. This should be the height of the view for most implementations.
    */
    Warbird(QPixmap* mp, int nx, int ny, int maxX, int maxY);
    /**The requisite move function for any thing object.
    * This will also set the random movements.*/
    void move();

private:
    int mx;
    int my;
    int counter;
    int targetTime;
};

#endif
