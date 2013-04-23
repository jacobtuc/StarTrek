#include "car_select.h"

CarSelect::CarSelect(QPixmap* map, SelectCar* parent)
{
  parent_ = parent;
  setPixmap(*map);
  myMap = map;
}

CarSelect::~CarSelect()
{
  
}

void CarSelect::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  e = e;
  parent_->selectCar(myMap);
}
