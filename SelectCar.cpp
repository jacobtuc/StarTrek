#include "SelectCar.h"

SelectCar::SelectCar(QString name, MainWindow* parent)
{
  parent_ = parent;
  
  //Create the scene
  scene_ = new QGraphicsScene();
  setScene(scene_);
  
  // Create the text
  QString labelString("Choose your vehicle!");
  QGraphicsTextItem* label_ = new QGraphicsTextItem(labelString);
  QFont theFont("Helvetica [Cronyx]",35,QFont::Bold);
  label_->setFont(theFont);
  scene_->addItem(label_);
  
  // Create the cars
  // We need a variable to store the size in
  int carSize;
  QPixmap** cars = parent_->getCars(carSize);
  carViews_ = new CarSelect*[carSize];
  for (int n = 0; n < carSize; n++) {
    carViews_[n] = new CarSelect(cars[n],this);
    scene_->addItem(carViews_[n]);
  }
}

SelectCar::~SelectCar()
{
  
}

void SelectCar::selectCar(QPixmap* car)
{
  parent_->selectCar(car);
}
