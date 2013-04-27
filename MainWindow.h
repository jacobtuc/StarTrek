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
#include <QDockWidget>

#include "FirstWindowWidget.h"
#include "SelectCar.h"
#include "gameplay_window.h"
#include "ScoreDoc.h"
#include "AdminDock.h"

#define NUM_CARS 4
#define NUM_POLICE_CARS 2
#define NUM_STEERING_WHEELS 2

class AdminDock;
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
  /**This function updates the player's score in the top dock widget.
   * @param score The new score to be sent to the top dock widget. Note that this is not a change in score, but is the total score at that point in the game.
   */
  void updateScore(int score);
  /**This function updates the player's number of lives in the top dock widget.
   * @param lives The new number of lives to be sent to the top dock widget. Note that this is not a change in number of lives, but is the total number of lives at that point in the game.
   */
  void updateLives(int lives);
  /**This sets the admin variables that are false by default. These are to be called from the AdminDock and allow the user to force certain events to happen.*/
  void toggleAdminTools(bool boulder, bool tumbleweed, bool policeCar, bool computer);

private:
  FirstWindow* first_;
  SelectCar* second_;
  GameplayWindow* gameplay_;
  QApplication* parent_;
  ScoreDoc* scoreDock_;
  QDockWidget* topDock_;
  QDockWidget* rightDock_;
  AdminDock* adminDock_;
  QAction* pause_;
  bool paused;
  
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
  /**Creates a new game.
   * @post The game is taken back to the screen to select a car and the program restarts from there.The score and lives are reset as well as the condition of the pieces and the timer.*/
  void newGame();
  /**Pauses the game by calling the pase function in the gameplay window.*/
  void pauseGame();
};

#endif
