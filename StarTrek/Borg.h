#include "thing.h"

/**This class represents the Borg ship. It will move
* periodically to random locations on the screen.*/
class Borg : public Thing {
public:
    /**Default constructor.
    * @param mp The pixmap that should be loaded as the borg ship
    * @param nx The initial x position of the ship
    * @param ny The initial y position of the ship
    * @param mx The maximum x location of the ship. This should be the width of the third level landscape for most implementations.
    * @param my The maximum y location of the ship. This should be the height of the third level landscape for most implementations.*/
    Borg(QPixmap* mp, int nx, int ny, int mx, int my);
    /**The requisite move function of any Thing object. It will decide when to move and select a random location to move to.*/
    void move();

private:
    int counter;
    int nextMove,targetTime;
    int maxX,maxY;
};
