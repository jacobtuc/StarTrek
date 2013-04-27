#ifndef ADMINDOC_H
#define ADMINDOC_H

#include <QWidget>
#include <QBoxLayout>
#include <QCheckBox>

#include "MainWindow.h"
class MainWindow;

class AdminDock : public QWidget {
  Q_OBJECT
    public slots:
  void toggleCheckBoxes();

 public:
  AdminDock(MainWindow* parent_);
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
