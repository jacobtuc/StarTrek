#ifndef GAMEPLAY_WINDOW_H
#define GAMEPLAY_WINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QPoint>

#include "MainWindow.h"

class MainWindow;

/**This class contains the main gameplay.*/
class GameplayWindow : public QGraphicsView {
 public:
  /**Default constructor
     @param parent The MainWindow to which this window is the central widget
  */
  GameplayWindow(MainWindow* parent);
  /**Default Destructor*/
  ~GameplayWindow();
  /**Overloads the default method to draw the background. This will use the landscape from the MainWindow class to draw the background of the view. This will be called when the scene is passed to the view, so it should never be called externally.*/
  void drawBackground(QPainter *p, const QRectF &rect);

 private:
  QGraphicsScene* scene_;
  QPixmap* landscape_;
  
};

#endif
