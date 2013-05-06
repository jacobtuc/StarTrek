#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <QPixmap>

#include "thing.h"

class Enterprise : public Thing {
public:
    Enterprise(QPixmap* mp, int nx, int ny);
    ~Enterprise();
    void move();

private:

};

#endif
