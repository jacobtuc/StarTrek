#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(QApplication* parent)
{
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
}

void MainWindow::newGame()
{
  first_ = new FirstWindow(this);
  setCentralWidget(first_);
}
