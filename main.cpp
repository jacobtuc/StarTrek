#include <QtGui/QApplication>
#include "MainWindow.h"

/**This is the game of chicken. Two cars face each other and the first one to swerve is the chicken. Simple enough.*/
int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(&a);
  
  w.show();
  
  return a.exec();
}
