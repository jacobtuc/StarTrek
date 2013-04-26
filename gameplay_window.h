#ifndef GAMEPLAY_WINDOW_H
#define GAMEPLAY_WINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QPoint>
#include <QTimer>
#include <vector>

#include "MainWindow.h"
#include "PlayerCar.h"
#include "ComputerCar.h"
#include "Boulder.h"
#include "Tumbleweed.h"
#include "PoliceCar.h"
#include "SteeringWheel.h"

class MainWindow;
//class PlayerCar;
class ComputerCar;
//class Boulder;
//class Tumbleweed;
//class PoliceCar;

/**This class contains the main gameplay.*/
class GameplayWindow : public QGraphicsView {
  Q_OBJECT

 public:
  /**Default constructor
     @param parent The MainWindow to which this window is the central widget
  */
  GameplayWindow(MainWindow* parent);
  /**Default Destructor*/
  ~GameplayWindow();
  /**Overloads the default method to draw the background. This will use the landscape from the MainWindow class to draw the background of the view. This will be called when the scene is passed to the view, so it should never be called externally.*/
  void drawBackground(QPainter *p, const QRectF &rect);
  /**The function to be called by the computer car if it is going to throw the steering wheel
   * @post A steering wheel is created and its velocity set to be thrown out of the car.
   */
  void computerThrowWheel();
  /**This function is called from the MainWindow to indicate the up arrow was pressed. This increases the acceleration of the player's car by 1 until it reaches its maximum (+1)*/
  void upArrow();
  /**This function is called from the MainWindow to indicate that the down arrow was pressed. This decreases the acceleration of the player's car by 1 until it reaches its maximum (-2)*/
  void downArrow();
  /**This function is called from the MainWindow to indicate that the left arrow was pressed. This will make the player's car swerve.*/
  void leftArrow();
  /**This function is called from the MainWindow to indicate that the space bar was pressed. This will throw the player's steering wheel out and remove the ability to swerve.*/
  void spaceBar();
  

 private:
  MainWindow* parent_;
  QGraphicsScene* scene_;
  QPixmap* landscape_;
  QTimer* timer_;
  
  // Things
  std::vector<Thing*> things_;
  PlayerCar* players_car_;
  ComputerCar* computers_car_;

 public slots:
  void handleTimer();
};

#endif
