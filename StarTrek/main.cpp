#include <QtGui/QApplication>
#include "MainWindow.h"

/**This game is a star trek themed game with three levels where the playwer
* will fly through an astroid field, battle a Romulan Warbird, and battle a
* borg ship. I guess it might be kind of fun if you're into that kind of stuff.
*/
int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  MainWindow w(&a);

  w.show();

  return a.exec();
}
