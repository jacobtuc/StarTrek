#include "AdminDock.h"
#include <iostream>

AdminDock::AdminDock(MainWindow* parent)
{
  parent_ = parent;
  layout_ = new QBoxLayout(QBoxLayout::TopToBottom,this);
  boulder_ = new QCheckBox("Force Boulder");
  connect(boulder_,SIGNAL(clicked()),this,SLOT(toggleCheckBoxes()));
  tumbleweed_ = new QCheckBox("Force Tumbleweed");
  connect(boulder_,SIGNAL(clicked()),this,SLOT(toggleCheckBoxes()));
  police_car_ = new QCheckBox("Force Police Car");
  connect(police_car_,SIGNAL(clicked()),this,SLOT(toggleCheckBoxes()));
  computer_ = new QCheckBox("Force Computer to Swerve");
  connect(computer_,SIGNAL(clicked()),this,SLOT(toggleCheckBoxes()));
  layout_->addWidget(boulder_);
  layout_->addWidget(tumbleweed_);
  layout_->addWidget(police_car_);
  layout_->addWidget(computer_);
}

AdminDock::~AdminDock()
{
  
}

void AdminDock::toggleCheckBoxes()
{
  parent_->toggleAdminTools(boulder_->isChecked(),tumbleweed_->isChecked(),police_car_->isChecked(),computer_->isChecked());
}
