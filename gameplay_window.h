#ifndef GAMEPLAY_WINDOW_H
#define GAMEPLAY_WINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QPoint>
#include <QTimer>
#include <QMessageBox>
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
  /**This function will check if relevent items are colliding with each other and perform the appropriate actions if they are.*/
  void checkCollisions();
  /**Resets the pieces of the game for a new round, but does not reset lives or points.*/
  void newRound();
  /**This function will change the player's score. It can either add points or subtract points depending on the sign of the integer passed to it.
   * @param deltaScore The amount by which the score should be changed. This number can be positive (increase the score by the given amount) or negative (decrease the score by the given amount).
   * @post This function will call the lose game function if the score goes below zero. It will also call the appropriate functions to update score information in the main window. There is no need to check the score after calling this function.
   */
  void changeScore(int deltaScore);
  /**This function decrements the lives of the player by one. It should be called whenever the player is to lose a life. This function will call the lose game function if the player's lives go below zero. It will also call appropriate functions to update the lives information in the main window. There is no need to check the number of lives after calling this function.*/
  void loseLife();
  /**This is the function to be called when the player has lost the game.
   * @pre The number of lives the player has or their score goes BELOW zero.
   * @post A message is shown telling the player they lost the game. A new game is then started. There is no need to call the new game function after this function.
   */
  void loseGame();
  /**This function is used to pause or restart the game.
   * @param s The value that paused should be set to. This should be true to pause the game and false to restart the game.*/
  void setPaused(bool s);


 private:
  MainWindow* parent_;
  QGraphicsScene* scene_;
  QPixmap* landscape_;
  QTimer* timer_;
  
  // Things
  std::vector<Thing*> things_;
  PlayerCar* players_car_;
  ComputerCar* computers_car_;
  Boulder* boulder_;
  Tumbleweed* tumbleweed_;
  PoliceCar* police_car_;
  
  // Player score and lives
  int score_;
  int lives_;
  
  //Timer
  bool starting_;
  bool paused_;

 public slots:
  void handleTimer();
};

#endif
