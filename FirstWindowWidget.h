#ifndef FIRSTWINDOWWIDGET_H
#define FIRSTWINDOWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>

#include "MainWindow.h"

class MainWindow;

/**The first window to be displayed. This is a simple form for the user to enter their name.*/
class FirstWindow : public QWidget {
  Q_OBJECT

public:
  /**Default constructor
     @param parent The Main Window to which this First Window is the central widget.
  */
  FirstWindow(MainWindow* parent);
  /**Default destructor*/
  ~FirstWindow();
  /**Returns the name that the user has entered. There is no error testing, as a name could theoretically be anything. */
  QString getName();

private:
  QFormLayout *layout_;
  QLineEdit* name_;
  MainWindow* parent_;

public slots:
  /**The slot for the next button. This calls the selectCar() fucntion on the parent main window.*/
  void next();
};

#endif
