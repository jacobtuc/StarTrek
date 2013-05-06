#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <QPixmap>

#include "thing.h"

/**This is the player's object. It should show the image of the enterprise and have the velocities set by the key press events.
* Note that the velocity is set to zero every time the move function is called, meaning the object will only move while the arrow keys are being held.
* @author Jacob Tucker
*/
class Enterprise : public Thing {
public:
    /**Default constructor. The parameters are the same as the default constructor for Thing.
    * @see Thing
    */
    Enterprise(QPixmap* mp, int nx, int ny);
    /**Default destructor*/
    ~Enterprise();
    /**The move function to be called by the timer event.
    * @post This moves the object as per the x and y velocities and then sets both velocities equal to zero so the ship only moves when the arrow keys are being held down.*/
    void move();
    /**Sets the velocity in the X direction.
    * @param nx The new X velocity.*/
    void setVelocityX(int nx);
    /**Sets the velocity in the Y direction
    * @param ny The new Y velocity.*/
    void setVelocityY(int ny);
};

#endif
