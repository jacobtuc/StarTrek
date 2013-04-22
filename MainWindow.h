#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

#include "FirstWindowWidget.h"

class FirstWindow;

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

private:
  FirstWindow* first_;
  QApplication* parent_;
  
  //Menus
  QMenu* file_;
  QMenu* view_;

  //User data
  QString name;

public slots:
  void newGame();
};

#endif
