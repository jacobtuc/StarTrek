#ifndef CAR_SELECT_H
#define CAR_SELECT_H

#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "SelectCar.h"

class SelectCar;

/**This class contains a single image of a car that can be selected. When selected, it will set itself as the user's car in the game. The object must be within a SelectCar object and have a SelectCar parent.*/
class CarSelect : public QGraphicsPixmapItem {
public slots:
  /**This is the function that is called when the item is clicked.
     @post This car will be set as the user's car and the gameplay will begin.*/
  void mousePressEvent(QGraphicsSceneMouseEvent* e);

 public:
  /**The default constructor
     @param map The pixmap to be displayed on the item. This should be from the MainWindow's cars array.
     @param parent The SelectCar object to which the item belongs
     @param posX The X position of the item in the scene
     @param posY The Y position of the item in the scene
  */
  CarSelect(QPixmap* map, SelectCar* parent, int posX, int posY);
  /**The default destructor*/
  ~CarSelect();

 private:
  SelectCar* parent_;
  QPixmap* myMap;
};

#endif
