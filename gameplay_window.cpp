#include "gameplay_window.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GameplayWindow::GameplayWindow(MainWindow* parent)
{
  parent_ = parent;

  // Seed the random number generator
  srand( time(NULL) );
  
  // Create the scene
  scene_ = new QGraphicsScene();
  setScene(scene_);
  
  // Set the size of the view to the size of the landscape
  landscape_ = parent->getLandscape();
  setSceneRect(0,0,landscape_->width(),landscape_->height());
  setFixedSize(landscape_->width()+10,landscape_->height()+10);
  
  // Create the player's car
  players_car_ = new PlayerCar(parent_->getPlayersCar(),landscape_->width()/2,landscape_->height()-parent_->getPlayersCar()->height());
  scene_->addItem(players_car_);
  things_.push_back(players_car_);

  // Pick and create the computer's car
  int carSize;
  QPixmap** cars =  parent_->getCars(carSize);
  QPixmap* computerPic;
  do {
    computerPic = cars[ rand() % carSize ];
  } while (computerPic == parent_->getPlayersCar());
  computers_car_ = new ComputerCar(computerPic, (landscape_->width()/2)+computerPic->width(),computerPic->height()+25, parent_->getPlayersCar()->height(),this);
  scene_->addItem(computers_car_);
  things_.push_back(computers_car_);
  
  // Create the boulder
  Boulder* aBoulder = new Boulder(parent_->getBoulder(),0,(landscape_->height()/2)-parent_->getBoulder()->height()/2, parent_->getPlayersCar()->height());
  scene_->addItem(aBoulder);
  things_.push_back(aBoulder);
  
  // Create the tumbleweed
  Tumbleweed* aTumbleweed = new Tumbleweed(parent_->getTumbleweed(),landscape_->width()-parent_->getTumbleweed()->width(), landscape_->height()/2,parent_->getPlayersCar()->width(), parent_->getPlayersCar()->height());
  scene_->addItem(aTumbleweed);
  things_.push_back(aTumbleweed);
  
  // Create the police cars
  int pcSize;
  QPixmap** pcs = parent_->getPoliceCars(pcSize);
  int pcSelec = rand() % pcSize;
  PoliceCar* pc1 = new PoliceCar(pcs[pcSelec],landscape_->width()/2,landscape_->height()+2);
  scene_->addItem(pc1);
  things_.push_back(pc1);
  int pc2Selec;
  do {
    pc2Selec = rand() % pcSize;
  } while(pcSelec == pc2Selec);
  PoliceCar* pc2 = new PoliceCar(pcs[pc2Selec],(landscape_->width()/2)+pcs[pc2Selec]->width(),0);
  scene_->addItem(pc2);
  things_.push_back(pc2);
  
  // Create the timer and start it
  timer_ = new QTimer(this);
  timer_->setInterval(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimer()));
  timer_->start();
}

GameplayWindow::~GameplayWindow()
{
  timer_->stop();
  delete timer_;
}

void GameplayWindow::drawBackground(QPainter *p, const QRectF &rect)
{
  QRectF newRect = rect;
  newRect = newRect;
  p->drawPixmap(QPoint(0,0),*landscape_);
}

void GameplayWindow::computerThrowWheel()
{
  int swSize;
  QPixmap** sws = parent_->getSteeringWheels(swSize);
  srand( time(NULL) );
  int selection = rand() % swSize;
  SteeringWheel* theWheel = new SteeringWheel(sws[selection],computers_car_->pos().x(),computers_car_->pos().y(),computers_car_->getVelocityY());
  scene_->addItem(theWheel);
  things_.push_back(theWheel);
}

void GameplayWindow::handleTimer()
{
  for(std::vector<Thing*>::iterator it  = things_.begin(); it != things_.end(); ++it) {
    (*it)->move();
  }
}

void GameplayWindow::upArrow()
{
  players_car_->incrementAccel();
}

void GameplayWindow::downArrow()
{
  players_car_->decrementAccel();
}

void GameplayWindow::leftArrow()
{
  players_car_->swerve();
}

void GameplayWindow::spaceBar()
{
  // Create the wheel and have it move
  int swSize;
  QPixmap** sws = parent_->getSteeringWheels(swSize);
  srand( time(NULL) );
  int selection = rand() % swSize;
  SteeringWheel* theWheel = new SteeringWheel(sws[selection],players_car_->pos().x(),players_car_->pos().y(),players_car_->getVelocityY());
  scene_->addItem(theWheel);
  things_.push_back(theWheel);
  
  // Set the acceleration and velocity of the players car
  // Also locks control of the car.
  players_car_->throwWheel();
}
