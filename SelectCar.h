#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "MainWindow.h"
#include "car_select.h"

class MainWindow;
class CarSelect;

/**This is the widget that will be displayed to allow the user to select what car they want to use.*/
class SelectCar : public QGraphicsView {
  Q_OBJECT
public slots:

public:
  /**Default constructor
     @param name The name of the user. This should have been retrieved from the first window while it was being displayed.
     @param parent The MainWindow to which this instance of SelectCar is a central widget.
  */
  SelectCar(QString name, MainWindow* parent);
  /**Default destructor*/
  ~SelectCar();
  /**This function is called from the CarSelect object when it is clicked.
     @param car The pixmap of the car to be selected
     @post The given pixmap is set as the user's car and the gameplay will begin.
  */
  void selectCar(QPixmap* car);

private:
  MainWindow* parent_;
  QGraphicsScene* scene_;
  CarSelect** carViews_;
};

#endif
