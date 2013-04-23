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
  
  // We'll make the width of the view the width of the text item
  QRectF labelSize = label_->boundingRect();
  
  // Create the cars
  // We need a variable to store the size in
  int carSize;
  QPixmap** cars = parent_->getCars(carSize);
  // Find out how many cars to have in a row
  int carWidth = cars[0]->width();
  int carHeight = cars[0]->height() + 5;
  int rowWidth = labelSize.width()/(carWidth+5);
  int currentHeight = labelSize.height()+10;
  int currentWidth = 0;
  carViews_ = new CarSelect*[carSize];
  for (int n = 0; n < carSize; n++) {
    carViews_[n] = new CarSelect(cars[n],this,currentWidth,currentHeight);
    currentWidth = currentWidth + carWidth;
    if (currentWidth == rowWidth*carWidth) {
      currentWidth = 0;
      currentHeight = currentHeight + carHeight;
    }
    scene_->addItem(carViews_[n]);
  }
  
  // Set the size of the view
  setFixedSize(labelSize.width(), currentHeight);
}

SelectCar::~SelectCar()
{
  
}

void SelectCar::selectCar(QPixmap* car)
{
  parent_->selectCar(car);
}
