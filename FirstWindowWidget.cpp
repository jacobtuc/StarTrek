#include "FirstWindowWidget.h"

FirstWindow::FirstWindow(MainWindow* parent)
{
  parent_ = parent;
  layout_ = new QFormLayout(this);
  name_ = new QLineEdit();
  layout_->addRow("Your Name:",name_);
  QPushButton* next = new QPushButton("Start Game");
  connect(next, SIGNAL(clicked()), this, SLOT(next()));
  layout_->addRow(next);
}

FirstWindow::~FirstWindow()
{
  
}

void FirstWindow::next()
{
  parent_->selectCar();
}

QString FirstWindow::getName()
{
  return name_->text();
}
