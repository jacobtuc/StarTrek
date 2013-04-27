#include "gameplay_window.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

GameplayWindow::GameplayWindow(MainWindow* parent)
{
  parent_ = parent;
  paused_ = false;
  parent_->setFocus();
  
  // The player starts with three lives and a score of 100.
  lives_ = 3;
  score_ = 100;

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
  boulder_ = new Boulder(parent_->getBoulder(),0,(landscape_->height()/2)-parent_->getBoulder()->height()/2, parent_->getPlayersCar()->height());
  scene_->addItem(boulder_);
  things_.push_back(boulder_);
  
  // Create the tumbleweed
  tumbleweed_ = new Tumbleweed(parent_->getTumbleweed(),landscape_->width()-parent_->getTumbleweed()->width(), landscape_->height()/2,parent_->getPlayersCar()->width(), parent_->getPlayersCar()->height());
  scene_->addItem(tumbleweed_);
  things_.push_back(tumbleweed_);
  
  // Create the police cars
  int pcSize;
  QPixmap** pcs = parent_->getPoliceCars(pcSize);
  int pcSelec = rand() % pcSize;
  police_car_ = new PoliceCar(pcs[pcSelec],landscape_->width()/2,landscape_->height()+2);
  scene_->addItem(police_car_);
  things_.push_back(police_car_);
  
  starting_ = false;
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
  if (paused_)
    return;
  if (starting_) {
    int timerInt = timer_->interval() - 12;
    // The timer interval can never be negative
    if (timerInt < 1)
      timerInt = 1;
    timer_->setInterval(timerInt);
    starting_ = false;
  }
  for(std::vector<Thing*>::iterator it  = things_.begin(); it != things_.end(); ++it) {
    if ((*it) == NULL)
      continue;
    (*it)->move();
  }
  checkCollisions();
}

void GameplayWindow::upArrow()
{
  players_car_->incrementAccel();
  boulder_->toggleMoving();
  tumbleweed_->toggleMoving();
  police_car_->toggleMoving();
}

void GameplayWindow::downArrow()
{
  players_car_->decrementAccel();
}

void GameplayWindow::leftArrow()
{
  players_car_->swerve();
  changeScore(-15);
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

void GameplayWindow::checkCollisions()
{
  if (players_car_->collidesWithItem(computers_car_)) {
      timer_->stop();
      QMessageBox collMsg;
      collMsg.setText("You have collided with the other player. Loss of 1 life will be applied.");
      collMsg.exec();
      changeScore(-25);
      loseLife();
      newRound();
  }
  else if (players_car_->collidesWithItem(boulder_)) {
    timer_->stop();
    QMessageBox collMsg;
    collMsg.setText("You just got killed by the boulder.");
    collMsg.exec();
    loseLife();
    newRound();
  }
  else if (players_car_->collidesWithItem(tumbleweed_)) {
    players_car_->setVisible(false);
    computers_car_->setVisible(false);
    boulder_->setVisible(false);
    police_car_->setVisible(false);
    tumbleweed_->setVisible(false);
  }
  else if (players_car_->collidesWithItem(police_car_)) {
    changeScore(-25);
    loseLife();
    QMessageBox caughtMsg;
    caughtMsg.setText("You've been caught by the police!");
    caughtMsg.exec();
    newRound();
  }
  else if (players_car_->pos().y() < 150) {
    QMessageBox winMsg;
    winMsg.setText("Congradulations! You won the round!");
    winMsg.exec();
    changeScore(50);
    newRound();
  } else if (players_car_->pos().x() > (1025-parent_->getTumbleweed()->width()-20)) {
    QMessageBox failMsg;
    failMsg.setText("CHICKEN!");
    failMsg.exec();
    changeScore(-15);
    newRound();
  }
}

void GameplayWindow::changeScore(int deltaScore)
{
  score_ = score_ + deltaScore;
  parent_->updateScore(score_);
  if (score_ < 0)
    loseGame();
}

void GameplayWindow::loseLife()
{
  lives_--;
  parent_->updateLives(lives_);
  if (lives_ < 0)
    loseGame();
}

void GameplayWindow::loseGame()
{
  QMessageBox loseMsg;
  loseMsg.setText("GAME OVER! YOU LOST!");
  loseMsg.exec();
  parent_->newGame();
}

void GameplayWindow::newRound()
{
  timer_->stop();
  //int tSize = things_.size();
  std::vector<Thing*>::iterator it;
  for (it = things_.begin(); it != things_.end(); ++it) {
    scene_->removeItem(*it);
  }
  things_.clear();
  /*
  for (int n = 0; n < tSize; n++) {
    if (things_[n] == NULL)
      continue;
    std::cout << "Removing item " << n << std::endl;
    scene_->removeItem(things_[n]);
    std::cout << "Erasing item " << n << std::endl;
    things_.erase(things_.begin()+n);
    } */
  
  // This should be almost identical to the constructor
  // because it is creating the conditions for a new game.
  // The only things that must be maintained are the timer
  // count, the score, and the number of lives.
  // Create the player's car

  // Seed the random number generator
  srand( time(NULL) );
  
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
  boulder_ = new Boulder(parent_->getBoulder(),0,(landscape_->height()/2)-parent_->getBoulder()->height()/2, parent_->getPlayersCar()->height());
  scene_->addItem(boulder_);
  things_.push_back(boulder_);
  
  // Create the tumbleweed
  tumbleweed_ = new Tumbleweed(parent_->getTumbleweed(),landscape_->width()-parent_->getTumbleweed()->width(), landscape_->height()/2,parent_->getPlayersCar()->width(), parent_->getPlayersCar()->height());
  scene_->addItem(tumbleweed_);
  things_.push_back(tumbleweed_);
  
  // Create the police cars
  int pcSize;
  QPixmap** pcs = parent_->getPoliceCars(pcSize);
  int pcSelec = rand() % pcSize;
  police_car_ = new PoliceCar(pcs[pcSelec],landscape_->width()/2,landscape_->height()+2);
  scene_->addItem(police_car_);
  things_.push_back(police_car_);
  
  starting_ = true;
  parent_->setFocus();
  timer_->start();
}

void GameplayWindow::setPaused(bool s)
{
  paused_ = s;
}

void GameplayWindow::toggleAdminTools(bool boulder, bool tumbleweed, bool policeCar, bool computer)
{
  boulder_->setShouldMove(boulder);
  tumbleweed_->setShouldMove(tumbleweed);
  police_car_->setShouldMove(policeCar);
  computers_car_->setDefSwerve(computer);
  parent_->setFocus();
}
