#include "gameplay_window.h"

GameplayWindow::GameplayWindow(MainWindow* parent)
{
  // Create the scene
  scene_ = new QGraphicsScene();
  setScene(scene_);
  
  // Set the size of the view to the size of the landscape
  landscape_ = parent->getLandscape();
  setSceneRect(0,0,landscape_->width(),landscape_->height());
  setFixedSize(landscape_->width(),landscape_->height());
}

GameplayWindow::~GameplayWindow()
{
}

void GameplayWindow::drawBackground(QPainter *p, const QRectF &rect)
{
  p->drawPixmap(QPoint(0,0),*landscape_);
}
