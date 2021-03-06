#include "BorgPhaser.h"
#include <iostream>

BorgPhaser::BorgPhaser(QPixmap* mp, int nx, int ny, int vx, int vy, int maxX, int maxY, GameplayWindow* parent) : Thing(mp,nx,ny)
{
    image = mp;
    vX = vx;
    vY = vy;
    mx = maxX;
    my = maxY;
    parent_ = parent;
    removing = false;
}

void BorgPhaser::move()
{
    if (removing)
        return;
    if (pos().x() < 0-image->width() || pos().x() > mx || pos().y() < 0-image->height() || pos().y() > my) {
        parent_->removeThing(this);
        removing = true;
        return;
    }
    setPos(pos().x() + vX,pos().y() + vY);
}

void BorgPhaser::setVelocity(int nx, int ny)
{
    nx = nx;
    ny = ny;
    return;
}
