#include "car_select.h"

CarSelect::CarSelect(QPixmap* map, SelectCar* parent, int posX, int posY)
{
  parent_ = parent;
  setPixmap(*map);
  myMap = map;
  setPos(posX,posY);
}

CarSelect::~CarSelect()
{
  
}

void CarSelect::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  e = e;
  parent_->selectCar(myMap);
}
