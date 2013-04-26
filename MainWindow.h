#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>
#include <QKeyEvent>

#include "FirstWindowWidget.h"
#include "SelectCar.h"
#include "gameplay_window.h"

#define NUM_CARS 4
#define NUM_POLICE_CARS 2
#define NUM_STEERING_WHEELS 2

class FirstWindow;
class SelectCar;
class GameplayWindow;

/**The main window of the application.
   This will contain all widgets for game play and everything to do with main gameplay. */
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  /**Default constructor
     @param The QApplication that owns the window. This is so the quit button on the file menu works.
  */
  MainWindow(QApplication* parent);
  /**Default destructor*/
  ~MainWindow();
  /**This is to be called when the name has been entered into the first window form. This function retrieves the name, removes the first window widget, and creates the window to select cars.
     @pre The first window object first_ must be created
     @post first_ is deleted and the second menu is created and displayed
  */
  void selectCar();
  /**Returns the array of pointers to car images.
     @param size A reference variable for the integer where you want the size of the array to be stored */
  QPixmap** getCars(int& size);
  /**Returns the array of pointers to steering wheel images.
     @param size A reference variable for the integer where you want the size of the array to be stored.*/
  QPixmap** getSteeringWheels(int& size);
  /**Returns the array of pointers to the police car images
     @param size A reference variable for the integer where you want the size of the array to be stored.*/
  QPixmap** getPoliceCars(int& size);
  /**Returns a pointer to the tumbleweed picture.*/
  QPixmap* getTumbleweed();
  /**Returns a pointer to the boulder picture.*/
  QPixmap* getBoulder();
  /**Returns a pointer to the landscape picture.*/
  QPixmap* getLandscape();
  /**Returns the car that the player has selected to use
     @pre The SelectCar window must have been created and the user must have selected a car.
  */
  QPixmap* getPlayersCar();
  /**This funtion is called from the SelectCar widget to indicate which car should be selected
     @param car The pixmap of the car to be the user's car. This should be a member of the cars array.
     @post car will be set as the user's car and the gameplay will begin
  */
  void selectCar(QPixmap* car);

private:
  FirstWindow* first_;
  SelectCar* second_;
  GameplayWindow* gameplay_;
  QApplication* parent_;
  
  //Menus
  QMenu* file_;
  QMenu* view_;

  //User data
  QString name;

  //Pictures
  QPixmap* cars_[NUM_CARS];
  QPixmap* police_cars_[NUM_POLICE_CARS];
  QPixmap* steering_wheels_[NUM_STEERING_WHEELS];
  QPixmap* tumbleweed_;
  QPixmap* boulder_;
  QPixmap* landscape_;
  QPixmap* playersCar_;

 protected:
  void keyPressEvent(QKeyEvent* e);

public slots:
  void newGame();
};

#endif
