#ifndef ADMINDOC_H
#define ADMINDOC_H

#include <QWidget>
#include <QBoxLayout>
#include <QCheckBox>

#include "MainWindow.h"
class MainWindow;

/**This is the dock to be used for grading purposes so certain objects (the boulder, tumbleweed, police car, and computer car) can be forced to exhibit their random behaviors.*/
class AdminDock : public QWidget {
  Q_OBJECT
    public slots:
  /**This is the slot that is called whenever a box is checked. It sends the updated values of each box to the gameplay window.*/
  void toggleCheckBoxes();

 public:
  /**The default constructor
   * @param parent_ The MainWindow on which the widget is placed*/
  AdminDock(MainWindow* parent_);
  /**Default destructor*/
  ~AdminDock();

 private:
  QCheckBox* boulder_;
  QCheckBox* tumbleweed_;
  QCheckBox* police_car_;
  QCheckBox* computer_;
  QBoxLayout* layout_;
  MainWindow* parent_;
};

#endif
