#include "Torpedo.h"
#include <math.h>
#include <iostream>

Torpedo::Torpedo(QPixmap* mp, int nx, int ny, Thing* target) : Thing(mp,nx,ny)
{
    playerTarget_ = false;
    target_ = target;
    Enterprise* playerTarg = dynamic_cast<Enterprise*>(target);
    if (playerTarg)
        playerTarget_ = true;

}

Torpedo::~Torpedo()
{
}

bool Torpedo::targetsPlayer()
{
    return playerTarget_;
}

void Torpedo::move()
{
    //std::cout << "Starting torpedo move" << std::endl;
    int xp = target_->pos().x();
    int yp = target_->pos().y();
    int x0 = pos().x();
    int y0 = pos().y();
    int vMax = 12;
    int vMaxSq = vMax*vMax;

    int numerator = ((xp-x0)*(xp-x0)) + ((yp-y0)*(yp-y0));
    int t = static_cast<int>(sqrt(numerator/vMaxSq));

    if (t == 0) {
        vX = (xp-x0);
        vY = (yp-y0);
    } else {
        vX = (xp-x0)/t;
        vY = (yp-y0)/t;
    }

    setPos(x0 + vX, y0 + vY);
    //std::cout << "Ending torpedo move" << std::endl;
}

Thing* Torpedo::getTarget()
{
    return target_;
}
