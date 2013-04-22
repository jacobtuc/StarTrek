#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QWidget>

#include "MainWindow.h"

class MainWindow;

/**This is the widget that will be displayed to allow the user to select what car they want to use.*/
class SelectCar : public QWidget {
  Q_OBJECT
public slots:
  void next();

public:
  /**Default constructor
     @param name The name of the user. This should have been retrieved from the first window while it was being displayed.
     @param parent The MainWindow to which this instance of SelectCar is a central widget.
  */
  SelectCar(QString name, MainWindow* parent);
  /**Default destructor*/
  ~SelectCar();

private:
  MainWindow* parent_;
}

#endif
