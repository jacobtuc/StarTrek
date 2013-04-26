#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QApplication* parent)
{
  setFocus();
  parent_ = parent;
  
  // Create the menu bar
  QMenuBar* mb = menuBar();
  
  //File
  file_ = new QMenu("File");
  QAction* newGame = new QAction("New Game", file_);
  connect(newGame,SIGNAL(triggered()),this,SLOT(newGame()));
  file_->addAction(newGame);
  QAction* quit = new QAction("Quit", file_);
  connect(quit,SIGNAL(triggered()),parent_,SLOT(quit()));
  file_->addAction(quit);
  mb->addMenu(file_);

  // Load the car images
  for (int n = 1; n < NUM_CARS+1; n++)
  {
    QString fileNum = QString::number(n);
    QString fileName = "Images/Img_Car" + fileNum + ".png";
    cars_[n-1] = new QPixmap(fileName);
  }
  
  // Load the police car images
  for (int n = 1; n < NUM_POLICE_CARS+1; n++)
  {
    QString fileNum = QString::number(n);
    QString fileName = "Images/Img_PC" + fileNum + ".png";
    police_cars_[n-1] = new QPixmap(fileName);
  }
  
  // Load the steering wheel images
  for (int n = 1; n < NUM_STEERING_WHEELS+1; n++)
  {
    QString fileNum = QString::number(n);
    QString fileName = "Images/Img_SW" + fileNum + ".png";
    steering_wheels_[n-1] = new QPixmap(fileName);
  }
  
  // Load the boulder, tumbleweed, and landscape.
  tumbleweed_ = new QPixmap("Images/Img_Tumbleweed.png");
  boulder_ = new QPixmap("Images/Img_Boulder.png");
  landscape_ = new QPixmap("Images/Landscape.png");
  
  //We start the program by displaying the first window (hence why it's called first window)
  first_ = new FirstWindow(this);
  setCentralWidget(first_);
}

MainWindow::~MainWindow()
{
  
}

void MainWindow::selectCar()
{
  name = first_->getName();
  second_ = new SelectCar(name,this);
  setCentralWidget(second_);
  show();
}

void MainWindow::newGame()
{
  first_ = new FirstWindow(this);
  setCentralWidget(first_);
}

/**********************
IMAGE GETTERS
**********************/
QPixmap** MainWindow::getCars(int& size)
{
  size = NUM_CARS;
  return cars_;
}

QPixmap** MainWindow::getSteeringWheels(int& size)
{
  size = NUM_STEERING_WHEELS;
  return steering_wheels_;
}

QPixmap** MainWindow::getPoliceCars(int& size)
{
  size = NUM_POLICE_CARS;
  return police_cars_;
}

QPixmap* MainWindow::getTumbleweed()
{
  return tumbleweed_;
}

QPixmap* MainWindow::getBoulder()
{
  return boulder_;
}

QPixmap* MainWindow::getLandscape()
{
  return landscape_;
}

QPixmap* MainWindow::getPlayersCar()
{
  return playersCar_;
}

void MainWindow::selectCar(QPixmap* car)
{
  playersCar_ = car;
  gameplay_ = new GameplayWindow(this);
  setCentralWidget(gameplay_);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
  switch (e->key()) {
  case Qt::Key_Right:
    gameplay_->leftArrow();
    break;
  case Qt::Key_Up:
    gameplay_->upArrow();
    break;
  case Qt::Key_Down:
    gameplay_->downArrow();
    break;
  case Qt::Key_Space:
    gameplay_->spaceBar();
    break;
  default:
    break;
  }
}
